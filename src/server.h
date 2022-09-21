#pragma once
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include "message.h"
#include "sql.h"
#include "user.h"

class Server;
void session(Server&, const int);

void response(const int, const bool);
void response(const int, const Message&);
void response(const int);

class Server final
{
	private:
	// Connected clients
	std::unordered_map<std::thread::id, std::string> _clients;
	SQL _sql;

	void subscribe(const std::thread::id, const std::string&);
	void unsubscribe(const std::thread::id);
	bool subscribed(const std::thread::id)const noexcept;

	public:
	Server();
	Server(Server&) = delete;
	Server(Server&&) = delete;

	void run(const uint16_t);

	Server &operator=(Server&) = delete;
	Server &&operator=(Server&&) = delete;

	friend void session(Server&, const int);
};
