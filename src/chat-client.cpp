#include <exception>
#include <iostream>
#include <string>
#include "client.h"
#include "utils.h"

int main(int argv, char **args)
{
	try
	{
		Client c(argv > 1 ? std::string(*(args + 1)) : "127.0.0.1");
		c.start();
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
