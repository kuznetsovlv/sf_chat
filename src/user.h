#pragma once
#include <string>
#include "server.h"

extern const std::string ALL;

class User final
{
	private:
	std::string _login;
	std::string _fullName;
	std::string _password;

	User()noexcept;
	User(std::string, std::string, std::string)noexcept;

	public:
	User(User&) = delete;
	User(User&&) = delete;

	std::string login()const noexcept;
	std::string fullName()const noexcept;
	std::string password()const noexcept;

	User &operator=(User&) = delete;
	User &operator=(User&&) = delete;

	friend class Server;
};
