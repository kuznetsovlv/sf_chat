#pragma once
#include <string>

extern const std::string ALL;

class User final
{
	private:
	std::string _login;
	std::string _fullName;
	std::string _password;

	public:
	User()noexcept;
	User(std::string, std::string, std::string)noexcept;
	User(User&) = delete;

	std::string getLogin()const noexcept;
	std::string getFullName()const noexcept;
	std::string getPassword()const noexcept;

	void setFullName(std::string)noexcept;
	void setPassword(std::string)noexcept;

	User &operator=(User&) = delete;
};
