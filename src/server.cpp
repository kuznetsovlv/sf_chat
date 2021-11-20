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

Server *getServer()
{
	if(!server)
	{
		server = new Server();
	}

	return server;
}
