#include <string>
#include <map>
#include <vector>
#include "server.h"
#include "message.h"
#include "user.h"

Server *server = nullptr;

Server::Server()
{
	_users[ALL] = new User();
}

Server::~Server() {
	for(auto iter = _users.begin(); iter != _users.end(); ++iter)
	{
		delete iter->second;
	}
}

bool Server::hasUser(std::string login)const noexcept
{
	return _users.find(login) != _users.end();
}

bool Server::createUser(std::string login, std::string fullName, std::string password)
{
	if(hasUser(login))
	{
		return false;
	}

	_users[login] = new User(login, fullName, password);

	return true;
}

void Server::saveMessage(Message message)
{
	_messages.push_back(message);
}


Server *getServer()
{
	if(!server)
	{
		server = new Server();
	}

	return server;
}
