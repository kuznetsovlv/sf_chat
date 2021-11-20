#pragma once
#include <string>
#include <map>
#include <vector>
#include "message.h"
#include "user.h"

class Server final
{
	private:
	std::map<std::string, User*, std::less<std::string>> _users;
	std::vector<Message> _messages;

	Server();

	bool hasUser(std::string)const noexcept;
	bool createUser(std::string, std::string, std::string);
	void saveMessage(Message);

	public:
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server();

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend Server* getServer();
};

Server *getServer();
