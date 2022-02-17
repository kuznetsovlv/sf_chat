#include <chrono>
#include <ctime>
#include <string>

const std::string now()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string str(std::ctime(&now));
	str.pop_back();
	return str;
}
