#pragma once
#include <filesystem>
#include <memory>
#include "logger.h"
#include "message.h"

class MessageLogger final: public Logger
{
	public:
	MessageLogger();
	MessageLogger(const std::filesystem::path&);
	MessageLogger(MessageLogger&) = delete;
	MessageLogger(MessageLogger&&) = delete;

	void input(Message&);
	std::shared_ptr<Message>next();

	MessageLogger &operator=(MessageLogger&) = delete;
	MessageLogger &operator=(MessageLogger&&) = delete;
};
