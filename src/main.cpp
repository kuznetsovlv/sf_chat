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

		std::cout << "File size: " << f.bytes() << " bytes" << std::endl;
		std::cout << "Size: " << f.lines() << std::endl;
		for(size_t i = 0; i < f.lines(); ++i)
		{
			std::cout << "Line " << i << ": " << f.getLine(i) << std::endl;
		}

		f.output("line 1");
		f.output("line 2");
		f.output("line 3");
		f.output("line 4");
		std::cout << "File size: " << f.bytes() << " bytes" << std::endl;
		std::cout << "Size: " << f.lines() << std::endl;

		std::cout << f.getLine(0) << std::endl;
		std::cout << f.getLine(2) << std::endl;
		std::cout << f.getLine(1) << std::endl;
		std::cout << f.getLine(3) << std::endl;
		std::cout << f.getLine(3) << std::endl;
		std::cout << f.getLine(f.lines() - 1) << std::endl;
		std::cout << f.getLine(f.lines()) << std::endl;

		f.output("line 5");
		std::cout << "File size: " << f.bytes() << " bytes" << std::endl;
		std::cout << "Size: " << f.lines() << std::endl;
		std::cout << f.getLine(4) << std::endl;
		for(size_t i = 0; i < f.lines(); ++i)
		{
			std::cout << "Line " << i << ": " << f.getLine(i) << std::endl;
		}
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
