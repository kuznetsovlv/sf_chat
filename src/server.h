#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "dataResponse.h"
#include "message.h"
#include "response.h"
#include "request.h"

class Client;
class User;
class Server final:public std::enable_shared_from_this<Server>
{
	private:
	std::map<std::string, std::shared_ptr<User>> _users;
	std::map<std::string, size_t> _sent;
	std::vector<Message> _messages;
	std::vector<std::shared_ptr<Client>> _clients;

	Server();

	bool hasUser(std::string)const noexcept;
	void createUser(std::string, std::string, std::string);
	void saveMessage(Message);
	void subscribe(std::shared_ptr<Client>);
	void unsubscribe(std::shared_ptr<Client>);
	bool subscribed(std::shared_ptr<Client> )const noexcept;
	const Message &message(std::string);

	public:
	Server(Server&) = delete;
	Server(Server&&) = delete;

	Response request(RegistrationRequest&)noexcept;
	DataResponse<std::shared_ptr<User>> request(LoginRequest&)noexcept;
	Response request(LogoutRequest&)noexcept;
	Response request(SendMessageRequest&)noexcept;
	DataResponse<Message> request(GetMessageRequest&)noexcept;

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend std::shared_ptr<Server> getServer();
};

std::shared_ptr<Server> getServer();
