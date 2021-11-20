#include <string>
#include "message.h"
#include "user.h"

Message::Message(std::string msg, std::string from, std::string to = ALL)noexcept:_msg(msg),_from(from),_to(to)
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
