#include <iostream>
#include <exception>
#include "client.h"
#include "server.h"

#include "messages.h"
#include "message.h"

int main()
{

	try
	{
		Messages m;
		std::cout << m.bytes() << std::endl;
		std::cout << m.messages() << std::endl;

		Message msg("test", "from", "to");

		m.save(msg);
		std::cout << m.messages() << std::endl;

		m.seek(0);
		while(true)
		{
			Message message = *m.next();
			if(message.empty())
			{
				break;
			}

			std::cout << message.date() << " - " << message.from() << " - " << message.to() << " - " << message.msg() << std::endl;
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
