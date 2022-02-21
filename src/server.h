#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include "dataResponse.h"
#include "message.h"
#include "messages.h"
#include "response.h"
#include "request.h"
#include "user.h"
#include "users.h"

class Client;
class Server final:public std::enable_shared_from_this<Server>
{
	private:
	Users _users;
	// Indexes of last messgae sent to each client
	std::unordered_map<std::shared_ptr<Client>, size_t> _send_from;
	// Messages
	Messages _messages;
	// Connected clients
	std::set<std::shared_ptr<Client>> _clients;

	bool hasUser(const std::string&);
	void createUser(const std::string&, const std::string&, const std::string&);
	void saveMessage(const Message&);
	void subscribe(std::shared_ptr<Client>);
	void unsubscribe(std::shared_ptr<Client>);
	bool subscribed(std::shared_ptr<Client> )const noexcept;
	const std::shared_ptr<Message> message(const std::shared_ptr<Client>);

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
