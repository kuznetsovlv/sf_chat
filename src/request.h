#pragma once
#include <string>
#include "message.h"

class Client;

class Request
{
	private:
	Client *_client;

	public:
	Request(Client*)noexcept;
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

class LogoutRequest final: public Request
{
	public:
	LogoutRequest(Client*)noexcept;
};

class SendMessageRequest final: public Request
{
	private:
	Message &_message;

	public:
	SendMessageRequest(Client*,Message&)noexcept;
	SendMessageRequest(SendMessageRequest&) = delete;
	SendMessageRequest(SendMessageRequest&&) = delete;

	Message &message()const noexcept;

	SendMessageRequest &operator=(SendMessageRequest&) = delete;
	SendMessageRequest &&operator=(SendMessageRequest&&) = delete;
};

class GetMessageRequest final: public Request
{
	public:
	GetMessageRequest(Client*)noexcept;
	GetMessageRequest(GetMessageRequest&) = delete;
	GetMessageRequest(GetMessageRequest&&) = delete;

	GetMessageRequest &operator=(GetMessageRequest&) = delete;
	GetMessageRequest &&operator=(GetMessageRequest&&) = delete;
};
