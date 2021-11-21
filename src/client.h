#pragma once
#include <string>
#include "message.h"
#include "server.h"
#include "user.h"

class Client final
{
	private:
	User *_user = nullptr;
	Server *_server = nullptr;

	void login();
	void logout() noexcept;

	public:
	Client(Server*) noexcept;
	~Client()noexcept;

	void start();

	void setMessage(Message&) const noexcept;
	std::string user()const noexcept;
};
