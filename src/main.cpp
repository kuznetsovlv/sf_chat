#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"

#include <string>
#include "user.h"
#include "users.h"

int main()
{

	try
	{
		Users users;
		const User u("user", "user name", "qwerty"), u2("user", "user name", "123"), u3("user3", "user2", "1234");

		std::cout << users.exists(u) << std::endl;

		if(!users.exists(u))
		{
			users.add(u);
		}

		std::cout << users.validate(u) << std::endl;
		std::cout << users.validate(u2) << std::endl;
		std::cout << users.validate(u3) << std::endl;

		if(!users.exists(u3))
		{
			users.add(u3);
		}

		std::cout << users.validate(u) << std::endl;
		std::cout << users.validate(u2) << std::endl;
		std::cout << users.validate(u3) << std::endl;
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
