#pragma once
#include <memory>
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
	const std::shared_ptr<Server> _server;
	bool _hasNewMessage = false;

	void chat();
	void login();
	bool loginAndChat(std::string&, std::string&);
	void logout() noexcept;
	void registerUser();
	void showMessages()noexcept;

	public:
	Client(std::shared_ptr<Server>) noexcept;
	Client(Client&) = delete;
	Client(Client&&) = delete;

	void start();

	void request(NewMessageServerRequest&)noexcept;
	std::string user()const noexcept;

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
