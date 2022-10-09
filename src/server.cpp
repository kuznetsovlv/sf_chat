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
#include "config.h"
#include "server.h"
#include "client.h"
#include "network_exception.h"
#include "message.h"
#include "send.h"
#include "sql.h"
#include "user.h"
#include "utils.h"

std::mutex serverMutex;

Server::Server()
{
	SQLBuilder builder;
	builder.withHost(DB_HOST);
	builder.withUserName(DB_USER);
	builder.withPassword(DB_PASSWORD);
	builder.withDataBase(DB_NAME);
	_sql = builder.build();
}

void Server::subscribe(const std::thread::id clientId, const std::string &login)
{
	_clients.insert({clientId, login});
}

void Server::unsubscribe(const std::thread::id clientId)
{
	for(auto it = _clients.begin(); it != _clients.end(); ++it)
	{
		if(it->first == clientId)
		{
			_clients.erase(it);
			return;
		}
	}
}

bool Server::subscribed(const std::thread::id clientId)const noexcept
{
	return _clients.find(clientId) != _clients.end();
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

	if(bindStatus == -1)
	{
		close(sockd);
		throw NetworkException("Socket binding failed");
	}

	if(listen(sockd, 5) == -1)
	{
		throw NetworkException("Socket is unable to listen for new connection");
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
		uint32_t lastMessageId = 0;
		std::shared_ptr<User> currentUser = nullptr;

		size_t bufferSize = 8 * (sizeof(uint32_t) + sizeof(uint32_t));
		while(true)
		{

			uint8_t *buffer = new uint8_t[bufferSize];
			read(connection, buffer, bufferSize);

			const rtype requestType = getType(buffer);

			switch(requestType)
			{
				case rtype::SIZE:
				{
					try
					{
						bufferSize = static_cast<size_t>(ntohl(*reinterpret_cast<uint32_t*>(buffer + sizeof(uint32_t))));
						response(connection, true);
					}
					catch(...)
					{
						response(connection, false);
					}
					break;
				}
				case rtype::REGISTRATION:
				{
					bool locked = false;
					try
					{
						std::shared_ptr<User> user = bytesToUser(buffer);
						bool success = false;
						guard.lock();
						locked = true;
						if(!server._sql.userExists(*user))
						{
							server._sql.saveUser(*user);
							success = true;
						}
						guard.unlock();
						locked = false;
						response(connection, success);
					}
					catch(...)
					{
						if(locked)
						{
							guard.unlock();
						}
						response(connection, false);
					}
					break;
				}
				case rtype::LOGIN:
				{
					bool locked = false;
					try
					{
						std::shared_ptr<User> user = bytesToUser(buffer);
						guard.lock();
						locked = true;
						const bool success = server._sql.validateUser(*user);
						if(success)
						{
							currentUser = user;
							server.subscribe(id, currentUser->login());
						}
						guard.unlock();
						locked = false;
						lastMessageId = 0;
						response(connection, success);
					}
					catch(...)
					{
						if(locked)
						{
							guard.unlock();
						}
						response(connection, false);
					}
					break;
				}
				case rtype::LOGOUT:
				{
					bool locked = false;
					currentUser = nullptr;
					lastMessageId = 0;
					try
					{
						guard.lock();
						locked = true;
						if(server.subscribed(id))
						{
							server.unsubscribe(id);
						}
						guard.unlock();
						locked = false;
						response(connection, true);
					}
					catch(...)
					{
						if(locked)
						{
							guard.unlock();
						}
						response(connection, false);
					}
					break;
				}
				case rtype::MESSAGE:
				{
					bool locked = false;
					try
					{
						const std::shared_ptr<Message> message = bytesToMessage(buffer);
						guard.lock();
						locked = true;
						server._sql.addMessage(*message);
						guard.unlock();
						locked = false;
						response(connection, true);
					}
					catch(...)
					{
						if(locked)
						{
							guard.unlock();
						}
						response(connection, false);
					}
					break;
				}
				case rtype::MESSAGE_ID:
					lastMessageId = bytesToMessageId(buffer);
				case rtype::EMPTY:
				{
					bool locked = false;
					try
					{
						guard.lock();
						locked = true;
						if(!server.subscribed(id))
						{
							guard.unlock();
							locked = false;
							response(connection, false);
							break;
						}
						const std::shared_ptr<Message> message = server._sql.getMessage(lastMessageId, currentUser->login());
						guard.unlock();
						locked = false;

						if(message)
						{
							response(connection, *message);
							lastMessageId = message->id();
						}
						else
						{
							response(connection);
						}
					}
					catch(...)
					{
						if(locked)
						{
							guard.unlock();
						}
						response(connection, false);
					}
					break;
				}
				default:
				{
					response(connection, false);
					thread.join();
					break;
				}
			}

			delete [] buffer;
		}

		thread.join();
	}
}

void response(const int connection, const bool success)
{
	uint32_t type = htonl(static_cast<uint32_t>(success ? rtype::SUCCESS : rtype::FAIL));
	write(connection, &type, sizeof(type));
}

void response(const int connection, const Message &message)
{
	size_t size;
	uint8_t *data = toBytes(message, size);
	addType(data, rtype::MESSAGE);

	send(connection, data, size);
	delete [] data;
}

void response(const int connection)
{
	const uint32_t type = htonl(static_cast<uint32_t>(rtype::EMPTY));
	send(connection, reinterpret_cast<const uint8_t*>(&type), sizeof(uint32_t));
}
