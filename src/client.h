#pragma once
#include <string>
#include <vector>
#include "message.h"
#include "server.h"
#include "serverRequest.h"
#include "request.h"
#include "response.h"
#include "user.h"

class Client final
{
	private:
	User *_user = nullptr;
	Server *_server;
	bool hasNewMessage = false;

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

	void request(NewMessageServerRequest&)noexcept;
	std::string user()const noexcept;

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
