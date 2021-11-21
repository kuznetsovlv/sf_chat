#pragma once
#include <string>
#include <vector>
#include "message.h"
#include "server.h"
#include "request.h"
#include "response.h"
#include "user.h"

class Client final
{
	private:
	User *_user = nullptr;
	Server *_server;

	void chat()const noexcept;
	void login();
	void logout() noexcept;
	void registerUser();

	public:
	Client(Server*) noexcept;
	Client(Client&) = delete;
	Client(Client&&) = delete;
	~Client()noexcept;

	void start();

	void setMessage(Message&) const noexcept;
	std::string user()const noexcept;

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
