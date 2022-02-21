#include <string>
#include "users.h"
#include "cripto.h"
#include "user.h"
#include "utils.h"

const char DELIMETER = 0x9;
const size_t FIELD_COUNT = 4;
const char PASSWORD_DELIMETER = ':';

Users::Users():File("users.data")
{
	if(!lines())
	{
		std::string line;
		std::string strs[] = {"Index", "Login", "FullName", "SHA1"};
		join(strs, FIELD_COUNT, DELIMETER, line);
		output(line);
	}
}

void Users::add(const User &user)
{
	std::string saltStr, hashStr, line;

	salt(saltStr);
	sha1String(saltStr + user.password(), hashStr);

	std::string strs[] = {std::to_string(users() + 1), user.login(), user.fullName(), saltStr + PASSWORD_DELIMETER + hashStr};
	join(strs, FIELD_COUNT, DELIMETER, line);
	output(line);
}

bool Users::exists(const User& user)
{
	return exists(user.login());
}

bool Users::exists(const std::string &login)
{
	std::string buff[FIELD_COUNT];
	for(size_t i = 1; i < lines(); ++i)
	{
		const std::string line = getLine(i);
		split(buff, FIELD_COUNT, DELIMETER, line);
		if(buff[1] == login)
		{
			return true;
		}
	}
	return false;
}

bool Users::validate(const User& user)
{
	return validate(user.login(), user.password());
}

bool Users::validate(const std::string &login, const std::string password)
{
	std::string buff[FIELD_COUNT];
	for(size_t i = 1; i < lines(); ++i)
	{
		const std::string line = getLine(i);
		split(buff, FIELD_COUNT, DELIMETER, line);
		if(buff[1] == login)
		{
			std::string passBuff[2];
			split(passBuff, 2, PASSWORD_DELIMETER, buff[3]);
			std::string hashStr;
			sha1String(passBuff[0] + password, hashStr);

			return hashStr == passBuff[1];
		}
	}
	return false;
}

std::shared_ptr<User> Users::user(const std::string &login, const std::string &password)
{
	std::string buff[FIELD_COUNT];
	for(size_t i = 1; i < lines(); ++i)
	{
		const std::string line = getLine(i);
		split(buff, FIELD_COUNT, DELIMETER, line);
		if(buff[1] == login)
		{
			std::string passBuff[2];
			split(passBuff, 2, PASSWORD_DELIMETER, buff[3]);
			std::string hashStr;
			sha1String(passBuff[0] + password, hashStr);

			if(hashStr == passBuff[1])
			{
				return std::make_shared<User>(login, buff[2], password);
			}
			return nullptr;
		}
	}
	return nullptr;
}

size_t Users::users()const noexcept
{
	return lines() - 1;
}
