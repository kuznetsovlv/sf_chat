#include <string>
#include "file.h"
#include "message.h"
#include "utils.h"
#include "messages.h"

const char DELIMETER = '\t';
const size_t FIELD_COUNT = 5;

Messages::Messages():File("messages.data"),_position(0)
{
	if(!lines())
	{
		std::string line;
		std::string strs[] = {"Index", "Date", "From", "To", "Message"};
		join(strs, FIELD_COUNT, DELIMETER, line);
		output(line);
	}
}

void Messages::seek(size_t position)noexcept
{
	_position = position;
}

std::shared_ptr<Message> Messages::next()
{
	std::string str = getLine(++_position);

	if(str.empty())
	{
		return nullptr;
	}

	std::string buff[FIELD_COUNT];

	split(buff, FIELD_COUNT, DELIMETER, str);
	return std::make_shared<Message>(buff[4], buff[2], buff[3], buff[1]);
}

size_t Messages::position()const noexcept
{
	return _position;
}

void Messages::save(Message &message)
{
	std::string line;
	std::string strs[] = {std::to_string(messages() + 1), now(), message.from(), message.to(), message.msg()};
	join(strs, FIELD_COUNT, DELIMETER, line);
	output(line);
}

size_t Messages::messages()const noexcept
{
	return lines() - 1;
}
