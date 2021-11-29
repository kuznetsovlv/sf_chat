#pragma once
#include <memory>
#include <string>
#include <vector>
#include "server.h"
#include "serverRequest.h"
#include "request.h"
#include "user.h"

class Client final: public std::enable_shared_from_this<Client>
{
	private:
	std::shared_ptr<User> _user;
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
	std::shared_ptr<Client> ptr()noexcept;

	void request(NewMessageServerRequest&)noexcept;
	const std::string &user()const noexcept;

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
