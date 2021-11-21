#pragma once
#include <string>
#include <map>
#include <vector>
#include "client.h"
#include "message.h"
#include "user.h"

class Server final
{
	private:
	std::map<std::string, User*, std::less<std::string>> _users;
	std::vector<Message> _messages;
	std::vector<Client> _clients;

	Server();

	bool hasUser(std::string)const noexcept;
	bool createUser(std::string, std::string, std::string);
	void saveMessage(Message);
	void subscribe(Client&);

	public:
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server();

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend Server* getServer();
};

Server *getServer();
