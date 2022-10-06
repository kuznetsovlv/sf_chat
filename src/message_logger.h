#pragma once
#include <filesystem>
#include <memory>
#include "logger.h"
#include "message.h"

class MessageLogger final: public Logger
{
	public:
	explicit MessageLogger()noexcept;
	MessageLogger(MessageLogger&) = delete;
	MessageLogger(MessageLogger&&) = delete;

	void output(Message&);
	std::shared_ptr<Message>next();

	MessageLogger &operator=(MessageLogger&) = delete;
	MessageLogger &operator=(MessageLogger&&) = delete;
};
