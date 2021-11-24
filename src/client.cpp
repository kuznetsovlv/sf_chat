#include <iostream>
#include <string>
#include "client.h"
#include "server.h"
#include "serverRequest.h"
#include "request.h"
#include "response.h"

Client::Client(Server *server)noexcept:_server(server)
{
}

Client::~Client()noexcept
{
	deleteServer();
}

void Client::chat()
{
	showMessages();

	while(true)
	{
		if(_hasNewMessage)
		{
			showMessages();
		}

		std::cout << std::endl << "Enter your message. To send message to specific user enter \"@userName:\" at the begining. To quit chat enter \"!quit\"." << std::endl;

		std::string message;

		std::cin >> message;

		if(message == "!quit")
		{
			return;
		}
	}
}

void Client::logout() noexcept
{
	LogoutRequest request(this);
	std::cout << _server->request(request).message() << std::endl;
	_user = nullptr;
}

void Client::login()
{
	std::string login, password;

	for(unsigned i = 0; i < 3; ++i)
	{
		std::cout << "Login: ";
		std::cin >> login;
		std::cout << "Password: ";
		//TODO: Разобраться, как скрыть ввод.
		std::cin >> password;

		LoginRequest request(this, login, password);
		Response<User> response = _server->request(request);

		if(response.success())
		{
			_user = response.data();
			std::cout << "Welcom to the chat, " << _user->login() << "!" << std::endl;
			chat();
			return;
		}

		std::cout << response.message() << std::endl;
	}

	std::cout << "Authorisation failed!" << std::endl;
}

void Client::registerUser()
{
	std::string fullName, login, password1, password2;

	std::cout << "Enter your full name: ";
	std::cin >> fullName;
	std::cout << "Enter your login: ";
	std::cin >> login;

	do
	{
		//TODO: Разобраться, как скрыть ввод.
		std::cout << "Enter password: ";
		std::cin >> password1;
		std::cout << "Repeat password: ";
		std::cin >> password2;
	}
	while(password1 != password2);

	RegistrationRequest request(this, login, fullName, password1);

	Response<void> response = _server->request(request);

	if(response.success())
	{
		std::cout << "You are signed up successfully." << std::endl;
	}
	else
	{
		std::cout << response.message() << std::endl;
	}

	std::cout << std::endl;
}

void Client::showMessages()noexcept
{
	GetMessageRequest request(this);
	while(true)
	{
		Response<Message> response = _server->request(request);

		if(response.success())
		{
			Message *message = response.data();

			if(message)
			{
				std::cout << (message->from() == user() ? "Me:" : message->from()) << std::endl;

				if(message->to() != ALL)
				{
					std::cout << "@" << message->to() << ": ";
				}

				std::cout << message->msg() << std::endl;
			}
			else
			{
				_hasNewMessage = false;
				return;
			}
		}
		else
		{
			std::cout << response.message() << std::endl;
		}
	}
}

void Client::start()
{
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
}

void Client::request(NewMessageServerRequest &request)noexcept
{
	_hasNewMessage = true;
}

std::string Client::user()const noexcept
{
	return _user ? _user->login() : "";
}
