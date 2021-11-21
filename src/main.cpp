#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"

int main()
{
	try
	{
		Client client(getServer());
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
