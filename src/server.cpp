#include <exception>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "server.h"
#include "client.h"
#include "dataResponse.h"
#include "message.h"
#include "messages.h"
#include "response.h"
#include "serverRequest.h"
#include "user.h"

const Message emptyMessage;

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
	_clients.insert(client);
	_send_from[client] = 0;
}

void Server::unsubscribe(std::shared_ptr<Client> client)
{
	for(auto it = _clients.begin(); it != _clients.end(); ++it)
	{
		if(it->get() == client.get())
		{
			_clients.erase(it);
			for(auto sit = _send_from.begin(); sit != _send_from.end();++sit)
			{
				if(sit->first == client)
				{
					_send_from.erase(sit);
					return;
				}
			}
		}
	}
}

bool Server::subscribed(std::shared_ptr<Client> client)const noexcept
{
	return _clients.find(client) != _clients.end();
}

const std::shared_ptr<Message> Server::message(const std::shared_ptr<Client> client)
{
	size_t count = 0;
	const std::string login = client->user();
	_messages.seek(_send_from[client]);
	std::shared_ptr<Message> message;

	while(message = _messages.next())
	{
		if(message->to() == ALL || message->to() == client->user())
		{
			_send_from[client] = _messages.position();
			return message;
		}
	}

	return nullptr;
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
	std::shared_ptr<User> user = _users.user(request.login(), request.password());
	if(user)
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
				DataResponse<Message> response(true, "Ok", *message(request.client()));
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
