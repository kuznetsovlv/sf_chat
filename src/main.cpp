#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"
#include "file.h"

int main()
{

	try
	{
		File f("test");

		f.output("line 1");
		f.output("line 2");
		f.output("line 3");
		f.output("line 4");
		/*std::shared_ptr<Client> client = std::make_shared<Client>(std::make_shared<Server>());
		client->start();*/
	}
	catch(std::exception &error)
	{
		std::cerr << error.what() << std::endl;
		return 1;
	}

	return 0;
}
