#pragma once
#include <string>
#include <exception>
#include <mysql/mysql.h>

class DBException final: public std::exception
{
	const std::string _what;

	public:
	explicit DBException(const std::string&)noexcept;

	virtual const char *what()const noexcept override;
};

class SQLBuilder;

class SQL final
{
	private:
	MYSQL *_mysql;

	explicit SQL(MYSQL*)noexcept;

	const MYSQL_RES* query(const std::string&);

	public:
	SQL()noexcept;
	SQL(SQL&) = delete;
	SQL(SQL&&)noexcept;
	~SQL();

	SQL operator=(SQL&) = delete;
	SQL &operator=(SQL&&)noexcept;

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

