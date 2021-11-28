#include <memory>
#include <string>
#include <map>
#include <vector>
#include "client.h"
#include "server.h"
#include "serverRequest.h"
#include "message.h"
#include "user.h"

Server::Server()
{
	std::shared_ptr<User> all(new User());
	_users[ALL] = all;
}

bool Server::hasUser(std::string login)const noexcept
{
	return _users.find(login) != _users.end();
}

void Server::createUser(std::string login, std::string fullName, std::string password)
{
	std::shared_ptr<User> user(new User(login, fullName, password));
	_users[login] = user;
	_lastSent[login] = -1;
}

void Server::saveMessage(Message message)
{
	_messages.push_back(message);
	NewMessageServerRequest request;

	for(unsigned i = 0; i < _clients.size(); ++i)
	{
		std::shared_ptr<Client> client = _clients[i];

		if(message.to() == ALL || message.to() == client->user())
		{
			client->request(request);
		}
	}
}

void Server::subscribe(std::shared_ptr<Client> client)
{
	_clients.push_back(client);
}

void Server::unsubscribe(std::shared_ptr<Client> client)
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

bool Server::subscribed(std::shared_ptr<Client> client)const noexcept
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

std::shared_ptr<Message> Server::message(std::string login)
{
	for(int i = _lastSent[login] + 1; i < _messages.size(); ++i)
	{
		Message message = _messages[i];
		if(message.to() == ALL || message.to() == login)
		{
			_lastSent[login] = i;
			return std::shared_ptr<Message>(&_messages[i]);
		}
	}
	return nullptr;
}

std::shared_ptr<Server> Server::ptr()noexcept
{
	return shared_from_this();
}

Response<void> Server::request(RegistrationRequest &request)noexcept
{
	if(hasUser(request.login()) || request.login() == ALL)
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
		std::shared_ptr<User> user = _users[request.login()];

		if(user->password() == request.password())
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

std::shared_ptr<Server> getServer()
{
	static std::shared_ptr<Server> server(new Server());
	return server;
}
