#include <chrono>
#include <cstring>
#include <ctime>
#include <memory>
#include <string>
#include <arpa/inet.h>
#include "message.h"
#include "rtype.h"
#include "user.h"

extern const uint16_t SERVER_PORT = 2033;

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

uint8_t *toBytes(const Message &message, size_t &size)
{
	size = sizeof(uint32_t) + (message.from().size() + message.to().size() + message.msg().size() + message.date().size() + 4) * sizeof(char);

	uint8_t *data = new uint8_t[size];

	uint8_t *p = data;

	p += sizeof(uint32_t);
	strcpy(reinterpret_cast<char*>(p), message.from().c_str());

	p += (message.from().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.to().c_str());

	p += (message.to().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.msg().c_str());

	p += (message.msg().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), message.date().c_str());


	return data;
}

uint8_t *toBytes(const User &user, size_t &size)
{
	size = sizeof(uint32_t) + (user.login().size() + user.fullName().size() + user.password().size() + 3) * sizeof(char);

	uint8_t *data = new uint8_t[size];

	uint8_t *p = data;

	p += sizeof(uint32_t);
	strcpy(reinterpret_cast<char*>(p), user.login().c_str());

	p += (user.login().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), user.fullName().c_str());

	p += (user.fullName().size() + 1) * sizeof(char);
	strcpy(reinterpret_cast<char*>(p), user.password().c_str());

	return data;
}

std::shared_ptr<Message> bytesToMessage(const uint8_t *data)
{
	const char *p = reinterpret_cast<const char*>(data + sizeof(uint32_t));

	const std::string from = std::string(p);

	p += from.size() + 1;
	const std::string to = std::string(p);

	p += to.size() + 1;
	const std::string msg = std::string(p);

	p += msg.size() + 1;
	const std::string date = std::string(p);

	return std::make_shared<Message>(msg, from, to, date);
}

std::shared_ptr<User> bytesToUser(const uint8_t *data)
{
	const char *p = reinterpret_cast<const char*>(data + sizeof(uint32_t));

	const std::string login = std::string(p);

	p += login.size() + 1;
	const std::string fullName = std::string(p);

	p += fullName.size() + 1;
	const std::string password = std::string(p);

	return std::make_shared<User>(login, fullName, password);
}

void addType(uint8_t *data, const rtype type)
{
	const uint32_t network_type = htonl(static_cast<uint32_t>(type));

	memcpy(data, &network_type, sizeof(uint32_t));
}

const rtype getType(const uint8_t *data)
{
	return static_cast<rtype>(ntohl(*reinterpret_cast<const uint32_t*>(data)));
}
