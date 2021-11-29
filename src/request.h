#pragma once
#include <memory>
#include <string>
#include "message.h"

class Client;

class Request
{
	private:
	const std::shared_ptr<Client> _client;

	public:
	Request(const std::shared_ptr<Client>&)noexcept;
	Request(Request&) = delete;
	Request(Request&&) = delete;
	virtual ~Request() = 0;

	virtual const std::shared_ptr<Client> &client()const noexcept final;

	Request &operator=(Request&) = delete;
	Request &&operator=(Request&&) = delete;
};

class RegistrationRequest final: public Request
{
	private:
	const std::string _login;
	const std::string _fullName;
	const std::string _password;

	public:
	RegistrationRequest(const std::shared_ptr<Client>&,const std::string&,const std::string&,const std::string&)noexcept;
	RegistrationRequest(RegistrationRequest&) = delete;
	RegistrationRequest(RegistrationRequest&&) = delete;

	const std::string &login()const noexcept;
	const std::string &fullName()const noexcept;
	const std::string &password()const noexcept;

	RegistrationRequest &operator=(RegistrationRequest&) = delete;
	RegistrationRequest &&operator=(RegistrationRequest&&) = delete;
};

class LoginRequest final: public Request
{
	private:
	const std::string _login;
	const std::string _password;

	public:
	LoginRequest(const std::shared_ptr<Client>&,const std::string&,const std::string&)noexcept;
	LoginRequest(LoginRequest&) = delete;
	LoginRequest(LoginRequest&&) = delete;

	const std::string &login()const noexcept;
	const std::string &password()const noexcept;

	LoginRequest &operator=(LoginRequest&) = delete;
	LoginRequest &&operator=(LoginRequest&&) = delete;
};

class LogoutRequest final: public Request
{
	public:
	explicit LogoutRequest(const std::shared_ptr<Client>&)noexcept;
};

class SendMessageRequest final: public Request
{
	private:
	const Message &_message;

	public:
	SendMessageRequest(const std::shared_ptr<Client>&,const Message&)noexcept;
	SendMessageRequest(SendMessageRequest&) = delete;
	SendMessageRequest(SendMessageRequest&&) = delete;

	const Message &message()const noexcept;

	SendMessageRequest &operator=(SendMessageRequest&) = delete;
	SendMessageRequest &&operator=(SendMessageRequest&&) = delete;
};

class GetMessageRequest final: public Request
{
	public:
	explicit GetMessageRequest(const std::shared_ptr<Client>&)noexcept;
	GetMessageRequest(GetMessageRequest&) = delete;
	GetMessageRequest(GetMessageRequest&&) = delete;

	GetMessageRequest &operator=(GetMessageRequest&) = delete;
	GetMessageRequest &&operator=(GetMessageRequest&&) = delete;
};
