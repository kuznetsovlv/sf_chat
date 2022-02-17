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

	size_t pos = str.find(DELIMETER);
	std::string date = str.substr(++pos, pos = str.find(DELIMETER, pos));
	std::string from = str.substr(++pos, pos = str.find(DELIMETER, pos));
	std::string to = str.substr(++pos, pos = str.find(DELIMETER, pos));
	std::string message = str.substr(++pos, pos = str.find(DELIMETER, pos));

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
