#pragma once
#include <string>
#include "message.h"

class Client;

class Request
{
	private:
	Client *_client;

	public:
	Request(Client&)noexcept;
	Request(Request&) = delete;
	Request(Request&&) = delete;
	virtual ~Request() = 0;

	virtual Client *client()const noexcept final;

	Request &operator=(Request&) = delete;
	Request &&operator=(Request&&) = delete;
};

class RegistrationRequest final: public Request
{
	private:
	std::string _login;
	std::string _fullName;
	std::string _password;

	public:
	RegistrationRequest(Client*,std::string,std::string,std::string)noexcept;
	RegistrationRequest(RegistrationRequest&) = delete;
	RegistrationRequest(RegistrationRequest&&) = delete;

	std::string login()const noexcept;
	std::string fullName()const noexcept;
	std::string password()const noexcept;

	RegistrationRequest &operator=(RegistrationRequest&) = delete;
	RegistrationRequest &&operator=(RegistrationRequest&&) = delete;
};

class LoginRequest final: public Request
{
	private:
	std::string _login;
	std::string _password;

	public:
	LoginRequest(Client*,std::string,std::string)noexcept;
	LoginRequest(LoginRequest&) = delete;
	LoginRequest(LoginRequest&&) = delete;

	std::string login()const noexcept;
	std::string password()const noexcept;

	LoginRequest &operator=(LoginRequest&) = delete;
	LoginRequest &&operator=(LoginRequest&&) = delete;
};

class MessageRequest final: public Request
{
	private:
	Message &_message;

	public:
	MessageRequest(Client*,Message&)noexcept;
	MessageRequest(MessageRequest&) = delete;
	MessageRequest(MessageRequest&&) = delete;

	Message &message()const noexcept;

	MessageRequest &operator=(MessageRequest&) = delete;
	MessageRequest &&operator=(MessageRequest&&) = delete;
};
