#pragma once
#include <memory>
#include <string>
#include <set>
#include <vector>
#include "dataResponse.h"
#include "message.h"
#include "messages.h"
#include "response.h"
#include "request.h"
#include "user.h"
#include "users.h"

class Server final
{
	private:
	int _sockd;
	Users _users;
	// Messages
	Messages _messages;
	// Connected clients
	std::set<uint32_t> _clients;

	bool hasUser(const std::string&);
	void createUser(const std::string&, const std::string&, const std::string&);
	void saveMessage(const Message&);
	void subscribe(uint32_t);
	void unsubscribe(uint32_t);
	bool subscribed(uint32_t )const noexcept;
	const std::shared_ptr<Message> message(const uint32_t);

	public:
	Server();
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server();

	void start();

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

};
