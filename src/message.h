#pragma once
#include <string>

class Message final
{
	private:
	std::string _msg;
	std::string _from;
	std::string _to;

	public:
	Message(std::string, std::string, std::string)noexcept;

	std::string from()const noexcept;
	std::string to()const noexcept;
	std::string msg()const noexcept;
};
