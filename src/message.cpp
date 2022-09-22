#include <string>
#include "message.h"
#include "user.h"

Message::Message()noexcept:_id(0),_empty(true){}

Message::Message(const std::string &msg, const std::string &from, const std::string &to = ALL)noexcept:_msg(msg),_from(from),_to(to),_id(0),_empty(false){}

Message::Message(const std::string &msg, const std::string &from, const std::string &to, const std::string &date)noexcept:Message(msg, from, to, date, 0){}

Message::Message(const std::string &msg, const std::string &from, const std::string &to, const std::string &date, const uint32_t id = 0)noexcept:_msg(msg),_from(from),_to(to),_date(date),_id(id),_empty(false){}

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

const std::string &Message::date()const noexcept
{
	return _date;
}

const uint32_t Message::id()const noexcept
{
	return _id;
}

bool Message::empty()const noexcept
{
	return _empty;
}
