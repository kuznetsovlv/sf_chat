#include <cstring>
#include <string>
#include "user.h"
#include "rtype.h"

const std::string ALL = "_ALL_";

User::User()noexcept:User(ALL, ALL, "")
{
}

User::User(std::string login, std::string fullName, std::string password)noexcept:_login(login),_fullName(fullName),_password(password)
{
}

const std::string &User::login()const noexcept
{
	return _login;
}

const std::string &User::fullName()const noexcept
{
	return _fullName;
}

const std::string &User::password()const noexcept
{
	return _password;
}
