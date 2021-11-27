#include <memory>
#include <string>
#include "request.h"
#include "client.h"
#include "message.h"

Request::Request(const std::shared_ptr<Client> client)noexcept:_client(client)
{
}

Request::~Request() = default;

const std::shared_ptr<Client> &Request::client()const noexcept
{
	return _client;
}

RegistrationRequest::RegistrationRequest(const std::shared_ptr<Client> client, std::string login, std::string fullName, std::string password)noexcept:Request(client),_login(login),_fullName(fullName),_password(password)
{
}

std::string RegistrationRequest::login()const noexcept
{
	return _login;
}

std::string RegistrationRequest::fullName()const noexcept
{
	return _fullName;
}

std::string RegistrationRequest::password()const noexcept
{
	return _password;
}

LoginRequest::LoginRequest(const std::shared_ptr<Client> client, std::string login, std::string password)noexcept:Request(client),_login(login),_password(password)
{
}

std::string LoginRequest::login()const noexcept
{
	return _login;
}

std::string LoginRequest::password()const noexcept
{
	return _password;
}

LogoutRequest::LogoutRequest(const std::shared_ptr<Client> client)noexcept:Request(client)
{
}

SendMessageRequest::SendMessageRequest(const std::shared_ptr<Client> client, Message &message)noexcept:Request(client),_message(message)
{
}

Message &SendMessageRequest::message()const noexcept
{
	return _message;
}

GetMessageRequest::GetMessageRequest(const std::shared_ptr<Client> client)noexcept:Request(client)
{
}
