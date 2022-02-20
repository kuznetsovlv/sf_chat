#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"

#include <string>
#include "cripto.h"
#include "user.h"
#include "users.h"

int main()
{

	try
	{
		std::string str;
		sha1String("qwerty", str);
		std::cout << str << std::endl;
		sha1String("123456", str);
		std::cout << str << std::endl;
		sha1String("qwerty", str);
		std::cout << str << std::endl;
		sha1String("123456", str);
		std::cout << str << std::endl;
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
