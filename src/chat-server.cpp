#include <exception>
#include <iostream>
#include "server.h"
#include "utils.h"

int main()
{
	try
	{
		Server s;
		s.run(SERVER_PORT);
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
