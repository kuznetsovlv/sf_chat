#pragma once
#include <mutex>
#include <string>
#include "message.h"
#include "message_logger.h"
#include "rtype.h"
#include "user.h"

class Client final
{
	private:
	const std::string _ip;
	const uint16_t _port;
	const int _sockd;
	std::string _login;
	MessageLogger _logger;
	std::mutex _ioMutex;
	std::mutex _networkMutex;

	void chat();
	void login();
	bool loginAndChat(const User&);
	void logout();
	void registerUser();
	bool request(const User&, const rtype);
	bool request(const Message&, const rtype);
	void networkMonitor();
	void showMessages();
	void input();

	public:
	explicit Client(const std::string&);
	Client(Client&) = delete;
	Client(Client&&) = delete;

	void start();

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
