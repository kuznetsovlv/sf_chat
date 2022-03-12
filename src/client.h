#pragma once
#include <string>
#include "message.h"
#include "rtype.h"
#include "user.h"

class Client final
{
	private:
	const std::string _ip;
	const uint16_t _port;
	const int _sockd;
	int _connection;

	void chat();
	void login();
	bool loginAndChat(std::string&, std::string&);
	void logout();
	void registerUser();
	bool request(const User&, const rtype);
	bool request(const Message&, const rtype);
	void showMessages();

	public:
	explicit Client(const std::string&);
	Client(Client&) = delete;
	Client(Client&&) = delete;

	void start();

	Client &operator=(Client&) = delete;
	Client &&operator=(Client&&) = delete;
};
