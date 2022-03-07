#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "client.h"
#include "message.h"
#include "messages.h"
#include "user.h"
#include "utils.h"

#include <iostream>

std::mutex serverMutex;

NetworkException::NetworkException(const char *what):_what(what)
{
}

const char *NetworkException::what()const noexcept
{
	return _what;
}

Server::Server()
{
	User all;
	if(!_users.exists(all))
	{
		_users.add(all);
	}
}

bool Server::hasUser(const std::string &login)
{
	return _users.exists(login);
}

void Server::createUser(const std::string &login, const std::string &fullName, const std::string &password)
{
	User user(login, fullName, password);
	_users.add(user);
}

void Server::saveMessage(const Message &message)
{
	_messages.save(message);
}

void Server::subscribe(const std::thread::id clientId, const std::string &login)
{
	_clients.insert({clientId, login});
	_sendFrom[clientId] = 0;
}

void Server::unsubscribe(const std::thread::id clientId)
{
	for(auto it = _clients.begin(); it != _clients.end(); ++it)
	{
		if(it->first == clientId)
		{
			_clients.erase(it);
			for(auto sit = _sendFrom.begin(); sit != _sendFrom.end();++sit)
			{
				if(sit->first == clientId)
				{
					_sendFrom.erase(sit);
					return;
				}
			}
		}
	}
}

bool Server::subscribed(const std::thread::id clientId)const noexcept
{
	return _clients.find(clientId) != _clients.end();
}

const std::shared_ptr<Message> Server::message(const std::thread::id clientId)
{
	if(subscribed(clientId))
	{
		size_t count = 0;
		_messages.seek(_sendFrom[clientId]);
		std::shared_ptr<Message> message;

		while(message = _messages.next())
		{
			if(message->to() == ALL || message->to() == _clients[clientId] || message->from() == _clients[clientId])
			{
				_sendFrom[clientId] = _messages.position();
				return message;
			}
		}
	}

	return nullptr;
}

void Server::run(const uint16_t port)
{
	const int sockd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockd == -1)
	{
		throw NetworkException("Socket creation failed");
	}

	struct sockaddr_in addr;

	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int bindStatus = bind(sockd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

	if(bindStatus ==-1)
	{
		close(sockd);
		throw NetworkException("Socket binding failed");
	}

	while(true)
	{
		std::thread thread(session, std::ref(*this), sockd);

		thread.join();
	}

	close(sockd);
}

void session(Server &server, const int sockd)
{
	std::unique_lock<std::mutex> guard(serverMutex, std::defer_lock);

	std::thread::id id = std::this_thread::get_id();
	struct sockaddr_in client;
	socklen_t length = sizeof(client);

	int connection = accept(sockd, reinterpret_cast<struct sockaddr*>(&client), &length);

	if(connection != -1)
	{
		std::thread thread(session, std::ref(server), sockd);

		size_t bufferSize = 8 * (sizeof(uint32_t) + sizeof(uint32_t));
		while(true)
		{

			uint8_t *buffer = new uint8_t[bufferSize];
			read(connection, reinterpret_cast<char*>(buffer), bufferSize / sizeof(char));

			const rtype requestType = getType(buffer);

			if(requestType == rtype::SIZE)
			{
				bufferSize = ntohl(*reinterpret_cast<uint32_t*>(buffer + sizeof(uint32_t)));
			}
			else
			{
				switch(requestType)
				{
					case rtype::REGISTRATION:
					{
						std::shared_ptr<User> user = bytesToUser(buffer);
						bool success = false;
						guard.lock();
						if(!server.hasUser(user->login()))
						{
							server.createUser(user->login(), user->fullName(), user->password());
							success = true;
						}
						guard.unlock();
						response(connection, success);
						break;
					}
				}
			}

			delete [] buffer;
		}
	}
}

void response(const int connection, const bool success)
{
	uint32_t type = htonl(static_cast<uint32_t>(success ? rtype::SUCCESS : rtype::FAIL));
	write(connection, &type, sizeof(type));
}
