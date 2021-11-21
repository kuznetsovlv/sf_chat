#pragma once
#include <string>
#include <map>
#include <vector>
#include "message.h"
#include "request.h"

class Client;
class User;
class Server final
{
	private:
	std::map<std::string, User*> _users;
	std::vector<Message> _messages;
	std::vector<Client*> _clients;

	Server();

	bool hasUser(std::string)const noexcept;
	bool createUser(std::string, std::string, std::string);
	void saveMessage(Message);
	void subscribe(Client*);

	public:
	Server(Server&) = delete;
	Server(Server&&) = delete;
	~Server();

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend Server* getServer();
};

Server *getServer();

void deleteServer();
