#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "message.h"
#include "response.h"
#include "request.h"

class Client;
class User;
class Server final:public std::enable_shared_from_this<Server>
{
	private:
	std::map<std::string, std::shared_ptr<User>> _users;
	std::map<std::string, int> _lastSent;
	std::vector<Message> _messages;
	std::vector<std::shared_ptr<Client>> _clients;

	Server();

	bool hasUser(const std::string)const noexcept;
	void createUser(const std::string, const std::string, const std::string);
	void saveMessage(const Message);
	void subscribe(const std::shared_ptr<Client>);
	void unsubscribe(const std::shared_ptr<Client>);
	bool subscribed(const std::shared_ptr<Client> )const noexcept;
	std::shared_ptr<Message> message(const std::string);

	public:
	Server(Server&) = delete;
	Server(Server&&) = delete;

	std::shared_ptr<Server> ptr()noexcept;

	Response<void> request(const RegistrationRequest&)noexcept;
	Response<User> request(const LoginRequest&)noexcept;
	Response<void> request(const LogoutRequest&)noexcept;
	Response<void> request(const SendMessageRequest&)noexcept;
	Response<Message> request(const GetMessageRequest&)noexcept;

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend std::shared_ptr<Server> getServer();
};

std::shared_ptr<Server> getServer();
