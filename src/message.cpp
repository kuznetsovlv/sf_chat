#include <string>
#include "message.h"
#include "user.h"

Message::Message(const std::string msg, const std::string from, const std::string to = ALL)noexcept:_msg(msg),_from(from),_to(to)
{
}

std::string Message::from()const noexcept
{
	return _from;
}

std::string Message::to()const noexcept
{
	return _to;
}

std::string Message::msg()const noexcept
{
	return _msg;
}
