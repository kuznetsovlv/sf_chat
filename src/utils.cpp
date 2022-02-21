#include <chrono>
#include <ctime>
#include <string>

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