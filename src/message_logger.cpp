#include <filesystem>
#include <memory>
#include <string>
#include "message_logger.h"
#include "logger.h"
#include "message.h"
#include "utils.h"

const char GROUP_SEPARATOR = 0x1d;

MessageLogger::MessageLogger()noexcept
{
}

void MessageLogger::input(Message &message)
{
	if(message.empty())
	{
		return;
	}

	std::string result = std::to_string(message.id()) + GROUP_SEPARATOR + message.from() + GROUP_SEPARATOR + message.to() + GROUP_SEPARATOR + message.date() + GROUP_SEPARATOR + message.msg();
	Logger::input(result);
}

std::shared_ptr<Message> MessageLogger::next()
{
	std::string line;
	output(line);

	if(line.empty())
	{
		return nullptr;
	}

	std::string strs[5];

	split(strs, 5, GROUP_SEPARATOR, line);

	return std::make_shared<Message>(strs[4], strs[1], strs[2], strs[3], static_cast<uint32_t>(std::stoul(strs[0])));
}
