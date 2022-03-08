#pragma once
#include <exception>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include "message.h"
#include "messages.h"
#include "user.h"
#include "users.h"

class Server;
void session(Server&, const int);

void response(const int, const bool);
void response(const int, const Message&);
void response(const int);

class NetworkException final: public std::exception
{
	private:
	const char *_what;

	public:
	NetworkException(const char*);

	virtual const char *what()const noexcept override;
};

class Server final
{
	private:
	Users _users;
	// Messages
	Messages _messages;
	std::unordered_map<std::thread::id, size_t> _sendFrom;
	// Connected clients
	std::unordered_map<std::thread::id, std::string> _clients;

	bool hasUser(const std::string&);
	void createUser(const std::string&, const std::string&, const std::string&);
	void saveMessage(const Message&);
	void subscribe(const std::thread::id, const std::string&);
	void unsubscribe(const std::thread::id);
	bool subscribed(std::thread::id)const noexcept;
	const std::shared_ptr<Message> message(const std::thread::id);
	bool validate(const User&);

	public:
	Server();
	Server(Server&) = delete;
	Server(Server&&) = delete;

	void run(const uint16_t);

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend void session(Server&, const int);
};
