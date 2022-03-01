#include <chrono>
#include <cstring>
#include <ctime>
#include <memory>
#include <string>
#include <arpa/inet.h>
#include "message.h"
#include "rtype.h"
#include "user.h"

void now(std::string &res)
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string str(std::ctime(&now));
	str.pop_back();
	res = str;
}

void split(std::string *buff, const size_t buffSize, const char delimeter, const std::string &str)
{
	size_t from = 0;
	for(size_t i = 0; i < buffSize; ++i)
	{
		size_t to = str.find(delimeter, from);
		*(buff + i) = str.substr(from, to - from);
		from = to + 1;
	}
}

void join(const std::string *strs, const size_t count, const char delimeter, std::string &res)
{
	res = *strs;

	for(size_t i = 1; i < count; ++i)
	{
		res += delimeter;
		res += *(strs + i);
	}
}

uint8_t *toBytes(const uint32_t from_id, const Message &message, size_t &size)
{
	size = sizeof(uint32_t) + sizeof(rtype) + (message.from().size() + message.to().size() + message.msg().size() + message.date().size() + 4) * sizeof(char);

	uint8_t *data = new uint8_t[size];

	uint8_t *p = data;

	const uint32_t network_from_id = htonl(from_id);
	memcpy(p, &network_from_id, sizeof(uint32_t));

	p += (sizeof(uint32_t) + sizeof(rtype));
	strcpy(reinterpret_cast<char*>(p), message.from().c_str());

	p += (message.from().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.to().c_str());

	p += (message.to().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.msg().c_str());

	p += (message.msg().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.date().c_str());


	return data;
}

uint8_t *toBytes(const uint32_t from_id, const User &user, size_t &size)
{
	size = sizeof(uint32_t) + sizeof(rtype) + (user.login().size() + user.fullName().size() + user.password().size() + 3) * sizeof(char);

	uint8_t *data = new uint8_t[size];

	uint8_t *p = data;

	const uint32_t network_from_id = htonl(from_id);
	memcpy(p, &network_from_id, sizeof(uint32_t));

	p += (sizeof(uint32_t) + sizeof(rtype));
	strcpy(reinterpret_cast<char*>(p), user.login().c_str());

	p += (user.login().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), user.fullName().c_str());

	p += (user.fullName().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), user.password().c_str());

	return data;
}
