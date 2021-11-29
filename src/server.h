#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "dataResponse.h"
#include "message.h"
#include "response.h"
#include "request.h"
#include "user.h"

class Client;
class Server final:public std::enable_shared_from_this<Server>
{
	private:
	std::map<std::string, std::shared_ptr<User>> _users;
	std::map<std::string, size_t> _sent;
	std::vector<Message> _messages;
	std::vector<std::shared_ptr<Client>> _clients;

	bool hasUser(const std::string&)const noexcept;
	void createUser(const std::string&, const std::string&, const std::string&);
	void saveMessage(const Message&);
	void subscribe(std::shared_ptr<Client>);
	void unsubscribe(std::shared_ptr<Client>);
	bool subscribed(std::shared_ptr<Client> )const noexcept;
	const Message &message(const std::string&);

	public:
	Server();
	Server(Server&) = delete;
	Server(Server&&) = delete;

	Response request(RegistrationRequest&)noexcept;
	DataResponse<std::shared_ptr<User>> request(LoginRequest&)noexcept;
	Response request(LogoutRequest&)noexcept;
	Response request(SendMessageRequest&)noexcept;
	DataResponse<Message> request(GetMessageRequest&)noexcept;

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

};
