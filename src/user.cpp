#include <string>
#include "user.h"

const std::string ALL = "_ALL_";

User::User()noexcept:User(ALL, "", "")
{
}

User::User(std::string login, std::string fullName, std::string password)noexcept:_login(login),_fullName(fullName),_password(password)
{
}

std::string User::login()const noexcept
{
	return _login;
}

std::string User::fullName()const noexcept
{
	return _fullName;
}

std::string User::password()const noexcept
{
	return _password;
}
