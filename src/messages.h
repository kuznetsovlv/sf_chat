#pragma once
#include <string>
#include "file.h"
#include "message.h"
#include "user.h"

class Messages final: public File
{
	private:
	size_t _position;

	public:
	Messages();

	void seek(size_t)noexcept;
	std::shared_ptr<Message> next();
	size_t position()const noexcept;
	void save(const Message&);
	size_t messages()const noexcept;
};
