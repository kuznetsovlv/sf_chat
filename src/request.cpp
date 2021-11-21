#include <string>
#include "request.h"
#include "client.h"
#include "message.h"

Request::Request(Client &client)noexcept:_client(&client)
{
}

Request::~Request() = default;

Client *Request::client()const noexcept
{
	return _client;
}

RegistrationRequest::RegistrationRequest(Client &client, std::string login, std::string fullName, std::string password)noexcept:Request(client),_login(login),_fullName(fullName),_password(password)
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
