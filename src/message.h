#pragma once
#include <string>

class Message final
{
	private:
	const std::string _msg;
	const std::string _from;
	const std::string _to;
	const std::string _date;
	const bool _empty;

	public:
	Message()noexcept;
	Message(const std::string&, const std::string&, const std::string&)noexcept;
	Message(const std::string&, const std::string&, const std::string&, const std::string&)noexcept;

	const std::string &from()const noexcept;
	const std::string &to()const noexcept;
	const std::string &msg()const noexcept;
	const std::string &date()const noexcept;
	bool empty()const noexcept;
};
