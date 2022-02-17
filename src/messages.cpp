#include <string>
#include "file.h"
#include "message.h"
#include "utils.h"
#include "messages.h"

const char DELIMETER = '\t';

Messages::Messages():File("messages.data"),_position(0)
{
	if(!lines())
	{
		std::string line = "Index";
		line += DELIMETER;
		line += "Date";
		line += DELIMETER;
		line += "From";
		line += DELIMETER;
		line += "To";
		line += DELIMETER;
		line += "Message";
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
		return std::make_shared<Message>();
	}

	size_t pos1 = str.find(DELIMETER);
	size_t pos2 = str.find(DELIMETER, ++pos1);
	std::string date = str.substr(pos1, pos2 - pos1);
	pos1 = pos2;
	pos2 = str.find(DELIMETER, ++pos1);
	std::string from = str.substr(pos1, pos2 - pos1);
	pos1 = pos2;
	pos2 = str.find(DELIMETER, ++pos1);
	std::string to = str.substr(pos1, pos2 - pos1);
	pos1 = pos2;
	pos2 = str.find(DELIMETER, ++pos1);
	std::string message = str.substr(pos1, pos2 - pos1);

	return std::make_shared<Message>(message, from, to, date);
}

size_t Messages::position()const noexcept
{
	return _position;
}

void Messages::save(Message &message)
{
	output(std::to_string(messages() + 1) + DELIMETER + now() + DELIMETER + message.from() + DELIMETER + message.to() + DELIMETER + message.msg());
}

size_t Messages::messages()const noexcept
{
	return lines() - 1;
}
