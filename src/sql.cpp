#include <string>
#include <cstring>
#include <mysql/mysql.h>
#include "sql.h"
#include "utils.h"

DBException::DBException(const std::string& what)noexcept:_what(what){}

const char *DBException::what()const noexcept
{
	return _what.c_str();
}

SQL::SQL()noexcept:SQL(nullptr){}

SQL::SQL(MYSQL *mysql)noexcept:_mysql(mysql){}

SQL::SQL(SQL &&that)noexcept
{
	_mysql = that._mysql;
	that._mysql = nullptr;
}

SQL::~SQL()
{
	if(_mysql)
	{
		mysql_close(_mysql);
	}
}

const MYSQL_RES* SQL::query(const std::string& queryStr)
{
	if(mysql_query(_mysql, queryStr.c_str()))
	{
		throw DBException("Wrong query: '" + queryStr + "'");
	}

	return mysql_store_result(_mysql);
}

SQL &SQL::operator=(SQL &&that)noexcept
{
	_mysql = that._mysql;
	that._mysql = nullptr;

	return *this;
}

SQLBuilder::SQLBuilder()noexcept:_host(nullptr),_userName(nullptr),_password(nullptr),_db(nullptr),_port(0),_socket(nullptr),_flag(0){}

SQLBuilder::~SQLBuilder()noexcept
{
	clear<char>(_host);
	clear<char>(_userName);
	clear<char>(_password);
	clear<char>(_db);
	clear<char>(_socket);
}

void SQLBuilder::withHost(const std::string &host)
{
	_host = str2char(host);
}

void SQLBuilder::withUserName(const std::string &userName)
{
	_userName = str2char(userName);
}

void SQLBuilder::withPassword(const std::string &password)
{
	_password = str2char(password);
}

void SQLBuilder::withDataBase(const std::string &db)
{
	_db = str2char(db);
}

void SQLBuilder::withPort(const unsigned port)noexcept
{
	_port = port;
}

void SQLBuilder::withSocket(const std::string &socket)
{
	_socket = str2char(socket);
}

void SQLBuilder::withFlag(const unsigned flag)noexcept
{
	_flag = flag;
}

SQL SQLBuilder::build()const
{
	MYSQL *mysql = mysql_init(nullptr);

	if(!mysql)
	{
		throw DBException("Can not create MySQL-descriptor");
	}

	if(!mysql_real_connect(mysql, _host, _userName, _password, _db, _port, _socket, _flag))
	{
		throw DBException(std::string("Connection failed: '") + std::string(mysql_error(mysql)) + std::string(","));
	}

	return SQL(mysql);
}
