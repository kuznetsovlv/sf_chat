#include <string>
#include "message.h"
#include "user.h"

Message::Message()noexcept:_empty(true)
{
}

Message::Message(const std::string msg, const std::string from, const std::string to = ALL)noexcept:_msg(msg),_from(from),_to(to),_empty(false)
{
}

const std::string &Message::from()const noexcept
{
	return _from;
}

const std::string &Message::to()const noexcept
{
	return _to;
}

const std::string &Message::msg()const noexcept
{
	return _msg;
}

bool Message::empty()const noexcept
{
	return _empty;
}
