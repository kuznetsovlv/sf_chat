#pragma once
#include <string>

class Message final
{
	private:
	const std::string _msg;
	const std::string _from;
	const std::string _to;

	public:
	Message(const std::string, const std::string, const std::string)noexcept;

	std::string from()const noexcept;
	std::string to()const noexcept;
	std::string msg()const noexcept;
};
