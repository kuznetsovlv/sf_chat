#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "client.h"
#include "input.h"
#include "message.h"
#include "networkException.h"
#include "rtype.h"
#include "send.h"
#include "user.h"
#include "utils.h"

const std::string emptyStr;

Client::Client(const std::string &ip):_ip(ip),_port(SERVER_PORT),_sockd(socket(AF_INET, SOCK_STREAM, 0))
{
	if(_sockd == -1)
	{
		throw NetworkException("Creation of Socked failed");
	}
}

void Client::chat()
{
	while(true)
	{
		showMessages();

		std::cout << std::endl << "Enter your message. To send message to specific user enter \"@userName:\" at the begining. To quit chat enter \"!quit\"." << std::endl;

		std::string message;
		std::getline(std::cin, message);

		if(message == "!quit")
		{
			logout();
			return;
		}

		std::string to;

		if(message.front() == '@')
		{
			auto pos = message.find(':');

			if(pos == std::string::npos)
			{
				to = ALL;
			}
			else
			{
				to = message.substr(1, pos - 1);
				message.erase(0, pos + 1);
			}
		}
		else
		{
			to = ALL;
		}

		const Message msg(message, _login, to);

		if(!request(msg, rtype::MESSAGE) || !success(_sockd))
		{
			throw NetworkException("Sending message failed");
		}
	}
}

void Client::logout()
{
	const uint32_t logoutType = htonl(static_cast<uint32_t>(rtype::LOGOUT));
	write(_sockd, &logoutType, sizeof(uint32_t));

	if(!success(_sockd))
	{
		throw NetworkException("Server error");
	}
}

void Client::login()
{
	ignore();

	for(unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Login: ";
		std::string login;
		std::getline(std::cin, login);
		std::cout << "Password: ";
		//TODO: Разобраться, как скрыть ввод.
		std::string password;
		std::getline(std::cin, password);

		const User user(login, "", password);

		if(loginAndChat(user))
		{
			return;
		}
	}

	std::cout << "Authorisation failed!" << std::endl;
}

bool Client::loginAndChat(const User &user)
{
	if(request(user, rtype::LOGIN) && success(_sockd))
	{
		_login = user.login();
		std::cout << "Welcom to the chat, " << user.login() << "!" << std::endl;
		chat();
		return true;
	}

	std::cout << "Can not login user " << user.login() << "!" << std::endl;

	return false;

}

void Client::registerUser()
{
	std::cout << "Enter your full name: ";
	std::string fullName;
	ignore();
	std::getline(std::cin, fullName);
	std::string login;
	do
	{
		std::cout << "Enter your login (can not contain '@', ':' or any space characters): ";
		std::getline(std::cin, login);
	}while(!isLogin(login));

	std::string password1, password2;

	do
	{
		//TODO: Разобраться, как скрыть ввод.
		std::cout << "Enter password: ";
		std::getline(std::cin, password1);
		std::cout << "Repeat password: ";
		std::getline(std::cin, password2);
	}
	while(password1 != password2);

	const User user(login, fullName, password1);

	if(!request(user, rtype::REGISTRATION))
	{
		std::string what = "Can not send request to register user with login " + user.login() + " and password " + user.password();

		throw NetworkException(what.c_str());
	}

	if(success(_sockd))
	{
		std::cout << "You are signed up successfully." << std::endl;
		loginAndChat(user);
	}
	else
	{
		std::cout << "Signig up failed" << std::endl;
	}

	std::cout << std::endl;
}

bool Client::request(const User &user, const rtype type)
{
	size_t size;
	uint8_t *data = toBytes(user, size);
	addType(data, type);
	bool successSent = send(_sockd, data, size);
	delete [] data;

	return successSent;
}

bool Client::request(const Message &message, const rtype type)
{
	size_t size;
	uint8_t *data = toBytes(message, size);
	addType(data, type);
	bool successSent = send(_sockd, data, size);
	delete [] data;

	return successSent;
}

void Client::showMessages()
{
	const uint32_t emptyType = htonl(static_cast<uint32_t>(rtype::EMPTY));
	const uint32_t successType = htonl(static_cast<uint32_t>(rtype::SUCCESS));
	while(true)
	{
		write(_sockd, &emptyType, sizeof(uint32_t));

		uint8_t sizeData[2 * sizeof(uint32_t)];
		read(_sockd, sizeData, 2 *sizeof(uint32_t));

		if(getType(sizeData) == rtype::SIZE)
		{
			const size_t size = static_cast<size_t>(ntohl(*reinterpret_cast<uint32_t*>(sizeData + sizeof(uint32_t))));
			uint8_t *data = new uint8_t[size];
			write(_sockd, reinterpret_cast<const uint8_t*>(&successType), sizeof(uint32_t));
			read(_sockd, data, size);

			switch(getType(data))
			{
				case rtype::EMPTY:
				{
					delete [] data;
					return;
				}
				case rtype::MESSAGE:
				{
					std::shared_ptr<Message> message = bytesToMessage(data);
					std::cout << std::endl;
					std::cout << (message->from() == _login ? "Me" : message->from()) << " (" << message->date() << "):" << std::endl;
					if(message->to() != ALL)
					{
						std::cout << "@" << message->to() << ": ";
					}

					std::cout << message->msg() << std::endl << std::endl;

					delete [] data;
					break;
				}
				default:
				{
					delete [] data;
					throw NetworkException("Server error. Message data failed.");
				}
			}
		}
		else
		{
			throw NetworkException("Server error. Message size failed.");
		}
	}
}

void Client::start()
{
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(_ip.c_str());
	server.sin_port = htons(_port);
	server.sin_family = AF_INET;

	if(connect(_sockd, reinterpret_cast<struct sockaddr*>(&server), sizeof(server)) == -1)
	{
		throw NetworkException("Connection with the server failed");
	}
	std::cout << "Greetings in our chat!" << std::endl;

	char comand;

	do
	{
		std::cout << "To chatting you must be authorised." << std::endl;
		std::cout << "I - sign in" << std::endl << "U - sign up" << std::endl << "Q - quit" << std::endl;
		std::cout << "Enter one (I/U/Q): ";
		std::cin >> comand;

		if(comand == 'I' || comand == 'i')
		{
			login();
		}
		if(comand == 'U' || comand == 'u')
		{
			registerUser();
		}
	} while(comand != 'q' && comand != 'Q');

	std::cout << "Bye!" << std::endl;
	close(_sockd);
}
