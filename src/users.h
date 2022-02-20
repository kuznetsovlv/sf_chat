#pragma once
#include <string>
#include "user.h"
#include "file.h"

class Users final: public File
{
	public:
	Users();

	void add(const User&);
	bool exists(const User&);
	bool validate(const User&);
	size_t users()const noexcept;
};
