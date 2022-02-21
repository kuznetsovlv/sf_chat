#pragma once
#include <string>
#include "file.h"
#include "user.h"

class Users final: public File
{
	public:
	Users();

	void add(const User&);
	bool exists(const User&);
	bool exists(const std::string&);
	bool validate(const User&);
	bool validate(const std::string&, const std::string);
	std::shared_ptr<User> user(const std::string&, const std::string&);
	size_t users()const noexcept;
};
