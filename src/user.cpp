#include <string>
#include "user.h"

const std::string ALL = "_ALL_";

User::User()noexcept:User(ALL, "", "")
{
}

User::User(std::string login, std::string fullName, std::string password)noexcept:_login(login),_fullName(fullName),_password(password)
{
}

std::string User::getLogin()const noexcept
{
	return _login;
}

std::string User::getFullName()const noexcept
{
	return _fullName;
}

std::string User::getPassword()const noexcept
{
	return _password;
}

void User::setFullName(std::string fullName)noexcept
{
	_fullName = fullName;
}

void User::setPassword(std::string password)noexcept
{
	_password = password;
}
