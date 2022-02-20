#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"

int main()
{

	try
	{
		std::shared_ptr<Client> client = std::make_shared<Client>(std::make_shared<Server>());
		client->start();
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
