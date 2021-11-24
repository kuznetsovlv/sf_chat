#include <string>
#include "request.h"
#include "client.h"
#include "message.h"

Request::Request(Client *client)noexcept:_client(client)
{
}

Request::~Request() = default;

Client *Request::client()const noexcept
{
	return _client;
}

RegistrationRequest::RegistrationRequest(Client *client, std::string login, std::string fullName, std::string password)noexcept:Request(client),_login(login),_fullName(fullName),_password(password)
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

LoginRequest::LoginRequest(Client *client, std::string login, std::string password)noexcept:Request(client),_login(login),_password(password)
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

LogoutRequest::LogoutRequest(Client *client)noexcept:Request(client)
{
}

SendMessageRequest::SendMessageRequest(Client *client, Message &message)noexcept:Request(client),_message(message)
{
}

Message &SendMessageRequest::message()const noexcept
{
	return _message;
}

GetMessageRequest::GetMessageRequest(Client *client)noexcept:Request(client)
{
}
