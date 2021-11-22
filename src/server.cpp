#include <string>
#include <map>
#include <vector>
#include "client.h"
#include "server.h"
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
}

void Server::saveMessage(Message message)
{
	_messages.push_back(message);
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
			}
			catch(...)
			{
				Response<User> response(false, "Unknown error.");
				return response;
			}
			Response<User> response(true, "Ok", user);
			return response;
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

Response<void> Server::request(MessageRequest &request)noexcept
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
