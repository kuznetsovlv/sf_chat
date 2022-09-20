#pragma once
#include <string>
#include <exception>
#include <memory>
#include <mysql/mysql.h>
#include "message.h"
#include "user.h"

#define DB_DEFAULT_HOST "localhost"

class DBException: public std::exception
{
	const std::string _what;

	public:
	explicit DBException(const std::string&)noexcept;

	virtual const char *what()const noexcept override;
};

class DBExceptionSoft final: public DBException
{
	public:
	explicit DBExceptionSoft(const std::string&)noexcept;
};

class SQLBuilder;

class SQL final
{
	private:
	MYSQL *_mysql;
	int32_t _allId;
	std::string _strAllId;

	explicit SQL(MYSQL*)noexcept;

	MYSQL_RES* query(const std::string&)const;

	public:
	SQL()noexcept;
	SQL(SQL&) = delete;
	SQL(SQL&&)noexcept;
	~SQL();

	SQL &operator=(SQL&) = delete;
	SQL &operator=(SQL&&)noexcept;

	int32_t getUserId(const std::string&)const;
	bool getLoginById(std::string&, const uint32_t)const;
	bool userExists(const User&)const;
	bool userExists(const std::string&)const;
	void saveUser(const User&)const;
	bool validateUser(const User&)const;
	void addMessage(const Message&)const;
	std::shared_ptr<Message>getMessage(const uint32_t, const std::string&)const;

	friend SQLBuilder;
};

class SQLBuilder final
{
	private:
	char *_host;
	char *_userName;
	char *_password;
	char *_db;
	unsigned _port;
	char *_socket;
	unsigned _flag;

	public:
	SQLBuilder()noexcept;
	~SQLBuilder()noexcept;

	void withHost(const std::string&);
	void withUserName(const std::string&);
	void withPassword(const std::string&);
	void withDataBase(const std::string&);
	void withPort(const unsigned)noexcept;
	void withSocket(const std::string&);
	void withFlag(const unsigned)noexcept;

	SQL build()const;
};
