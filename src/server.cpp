#include <string>
#include <map>
#include <vector>
#include "client.h"
#include "server.h"
#include "serverRequest.h"
#include "message.h"
#include "user.h"

Server *server = nullptr;

Server::Server()
{
	_users[ALL] = new User();
}

Server::~Server() {
	for(auto iter = _users.begin(); iter != _users.end(); ++iter)
	{
		delete iter->second;
	}
}

bool Server::hasUser(std::string login)const noexcept
{
	return _users.find(login) != _users.end();
}

void Server::createUser(std::string login, std::string fullName, std::string password)
{
	_users[login] = new User(login, fullName, password);
	_lastSent[login] = -1;
}

void Server::saveMessage(Message message)
{
	_messages.push_back(message);
	NewMessageServerRequest request;

	for(unsigned i = 0; i < _clients.size(); ++i)
	{
		Client *client = _clients[i];

		if(message.to() == ALL || message.to() == client->user())
		{
			client->request(request);
		}
	}
}

void Server::subscribe(Client *client)
{
	_clients.push_back(client);
}

void Server::unsubscribe(Client *client)
{
	for(unsigned i = 0; i < _clients.size(); ++i)
	{
		if(_clients[i] == client)
		{
			_clients.erase(_clients.begin() + i);
			return;
		}
	}
}

bool Server::subscribed(Client *client)const noexcept
{
	for(unsigned i = 0; i < _clients.size(); ++i)
	{
		if(_clients[i] == client)
		{
			return true;
		}
	}
	return false;
}

Message *Server::message(std::string login)
{
	for(int i = _lastSent[login] + 1; i < _messages.size(); ++i)
	{
		Message message = _messages[i];
		if(message.to() == ALL || message.to() == login)
		{
			_lastSent[login] = i;
			return &_messages[i];
		}
	}
	return nullptr;
}

Response<void> Server::request(RegistrationRequest &request)noexcept
{
	if(hasUser(request.login()))
	{
		Response<void> response(false, "User " + request.login() + " already exists.");
		return response;
	}

	try
	{
		createUser(request.login(), request.fullName(), request.password());
	}
	catch(...)
	{
		Response<void> response(false, "Can not ctreate user " + request.login() + ". Unknown error.");
		return response;
	}

	Response<void> response(true, "Ok");
	return response;
}

Response<User> Server::request(LoginRequest &request)noexcept
{
	if(hasUser(request.login()))
	{
		User *user = _users[request.login()];

		if(user->password() == request.login())
		{
			try
			{
				subscribe(request.client());
				Response<User> response(true, "Ok", user);
				return response;
			}
			catch(...)
			{
				Response<User> response(false, "Unknown error.");
				return response;
			}
		}
	}

	Response<User> response(false, "Incorrect login or password");
	return response;
}

Response<void> Server::request(LogoutRequest &request)noexcept
{
	try
	{
		unsubscribe(request.client());
	}
	catch(...)
	{
		Response<void> response(false, "Unknown error");
		return response;
	}

	Response<void> response(true, "Ok");
	return response;
}

Response<void> Server::request(SendMessageRequest &request)noexcept
{
	try
	{
		saveMessage(request.message());
	}
	catch(...)
	{
		Response<void> response(false, "Unknown error");
		return response;
	}

	Response<void> response(true, "Ok");
	return response;
}

Response<Message> Server::request(GetMessageRequest &request)noexcept
{
	if(subscribed(request.client()))
	{
		if(hasUser(request.client()->user()))
		{
			try
			{
				Response<Message> response(true, "Ok", message(request.client()->user()));
				return response;
			}
			catch(...)
			{
				Response<Message> response(false, "Unknown error");
				return response;
			}
		}

		Response<Message> response(false, "Unknown user");
		return response;
	}

	Response<Message> response(false, "Unsubscribed");
	return response;
}

Server *getServer()
{
	if(!server)
	{
		server = new Server();
	}

	return server;
}

void deleteServer() {
	if(server)
	{
		delete server;
		server = nullptr;
	}
}
