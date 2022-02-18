#pragma once
#include <memory>
#include <string>

extern const std::string ALL;

class User final: public std::enable_shared_from_this<User>
{
	private:
	const std::string _login;
	const std::string _fullName;
	const std::string _password;

	public:
	User()noexcept;
	User(std::string, std::string, std::string)noexcept;
	User(User&) = delete;
	User(User&&) = delete;

	const std::string &login()const noexcept;
	const std::string &fullName()const noexcept;
	const std::string &password()const noexcept;

	User &operator=(User&) = delete;
	User &operator=(User&&) = delete;
};
