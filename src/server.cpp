#include <exception>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "client.h"
#include "dataResponse.h"
#include "server.h"
#include "serverRequest.h"
#include "message.h"
#include "user.h"

const Message emptyMessage;

Server::Server()
{
	_users[ALL] = std::make_shared<User>();
}

bool Server::hasUser(const std::string &login)const noexcept
{
	return _users.find(login) != _users.end();
}

void Server::createUser(const std::string &login, const std::string &fullName, const std::string &password)
{
	_users[login] = std::make_shared<User>(login, fullName, password);
	_sent[login] = 0;
}

void Server::saveMessage(const Message &message)
{
	_messages.push_back(message);
	NewMessageServerRequest request;

	for(auto client: _clients)
	{
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
	for(size_t i = 0; i < _clients.size(); ++i)
	{
		if(_clients[i].get() == client.get())
		{
			_clients.erase(_clients.begin() + i);
			return;
		}
	}
}

bool Server::subscribed(std::shared_ptr<Client> client)const noexcept
{
	for(auto c: _clients)
	{
		if(c.get() == client.get())
		{
			return true;
		}
	}
	return false;
}

const Message &Server::message(const std::string &login)
{
	size_t count = 0;
	for(Message &message: _messages)
	{
		if(message.to() == ALL || message.to() == login)
		{
			++count;
			if (count > _sent[login])
			{
				++_sent[login];
				return message;
			}
		}
	}
	return emptyMessage;
}

Response Server::request(RegistrationRequest &request)noexcept
{
	if(hasUser(request.login()) || request.login() == ALL)
	{
		Response response(false, "User " + request.login() + " already exists.");
		return response;
	}

	try
	{
		createUser(request.login(), request.fullName(), request.password());
	}
	catch(std::exception &error)
	{
		Response response(false, "Can not ctreate user " + request.login() + ": " + std::string(error.what()));
		return response;
	}

	Response response(true, "Ok");
	return response;
}

DataResponse<std::shared_ptr<User>> Server::request(LoginRequest &request)noexcept
{
	if(hasUser(request.login()))
	{
		std::shared_ptr<User> user = _users[request.login()];

		if(user->password() == request.password())
		{
			try
			{
				subscribe(request.client());
				DataResponse<std::shared_ptr<User>> response(true, "Ok", user);
				return response;
			}
			catch(std::exception &error)
			{
				DataResponse<std::shared_ptr<User>> response("Can not login: " + std::string(error.what()));
				return response;
			}
		}
	}

	DataResponse<std::shared_ptr<User>> response(false, "Incorrect login or password", nullptr);
	return response;
}

Response Server::request(LogoutRequest &request)noexcept
{
	try
	{
		unsubscribe(request.client());
	}
	catch(std::exception &error)
	{
		Response response(false, error.what());
		return response;
	}

	Response response(true, "Ok");
	return response;
}

Response Server::request(SendMessageRequest &request)noexcept
{
	try
	{
		saveMessage(request.message());
	}
	catch(std::exception &error)
	{
		Response response(false, "Can not send message: " + std::string(error.what()));
		return response;
	}

	Response response(true, "Ok");
	return response;
}

DataResponse<Message> Server::request(GetMessageRequest &request)noexcept
{
	if(subscribed(request.client()))
	{
		if(hasUser(request.client()->user()))
		{
			try
			{
				DataResponse<Message> response(true, "Ok", message(request.client()->user()));
				return response;
			}
			catch(std::exception &error)
			{
				DataResponse<Message> response(false, "Can not get message: " + std::string(error.what()), emptyMessage);
				return response;
			}
		}

		DataResponse<Message> response(false, "Can not get message: unknown user", emptyMessage);
		return response;
	}

	DataResponse<Message> response(false, "Can not get message: unsubscribed", emptyMessage);
	return response;
}
