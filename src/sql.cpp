#include <string>
#include <cstdlib>
#include <memory>
#include <mysql/mysql.h>
#include "cripto.h"
#include "message.h"
#include "sql.h"
#include "user.h"
#include "utils.h"

const char PASSWORD_DELIMETER = ':';

DBException::DBException(const std::string &what)noexcept:_what(what){}

const char *DBException::what()const noexcept
{
	return _what.c_str();
}

DBExceptionSoft::DBExceptionSoft(const std::string &what)noexcept:DBException(what){};

SQL::SQL()noexcept:_mysql(nullptr){}

SQL::SQL(MYSQL *mysql)noexcept:_mysql(mysql)
{
	if(!userExists(ALL))
	{
		User all;
		saveUser(all);
	}

	_allId = getUserId(ALL);
	_strAllId = std::to_string(_allId);
}

SQL::SQL(SQL &&that)noexcept
{
	_mysql = that._mysql;
	_allId = that._allId;
	_strAllId = that._strAllId;
	that._mysql = nullptr;
}

SQL::~SQL()
{
	if(_mysql)
	{
		mysql_close(_mysql);
	}
}

MYSQL_RES* SQL::query(const std::string& queryStr)const
{
	if(mysql_query(_mysql, queryStr.c_str()))
	{
		throw DBException("Wrong query: '" + queryStr + "'");
	}

	return mysql_store_result(_mysql);
}

int32_t SQL::getUserId(const std::string &login)const
{
	MYSQL_ROW row = mysql_fetch_row(query("select id from users where login like '" + login + "'"));

	return row ? atoi(row[0]) : -1;
}

bool SQL::getLoginById(std::string &login, const uint32_t id)const
{
	MYSQL_ROW row = mysql_fetch_row(query("select login from users where id = " + std::to_string(id)));

	if(!row)
	{
		return false;
	}

	login = row[0];
	return true;
}

bool SQL::userExists(const User &user)const
{
	return userExists(user.login());
}

bool SQL::userExists(const std::string &login)const
{
	return !!mysql_fetch_row(query("select login from users where login like '" + login + "'"));
}

void SQL::saveUser(const User &user)const
{

	std::string saltStr, sha1;

	salt(saltStr);
	sha1String(saltStr + user.password(), sha1);

	sha1 = saltStr + PASSWORD_DELIMETER + sha1;

	if(userExists(user))
	{
		query("update users set full_name = '" + user.fullName() + "', sha1 = '" + sha1 + "' where login like '" + user.login() + "')");
	}
	else
	{
		query("insert into users(id, login, full_name, sha1) values(default, '" + user.login() + "', '" + user.fullName() + "', '" + sha1 + "')");
	}
}

bool SQL::validateUser(const User &user)const
{
	MYSQL_ROW row = mysql_fetch_row(query("select sha1 from users where login like '" + user.login() + "'"));

	if(row)
	{
		std::string sha1 = row[0];
		std::string buffer[2];
		split(buffer, 2, PASSWORD_DELIMETER, sha1);

		std::string currentSha1;
		sha1String(buffer[0] + user.password(), currentSha1);

		return currentSha1 == buffer[1];
	}

	return false;
}

void SQL::addMessage(const Message &message)const
{
	const uint32_t fromId = getUserId(message.from());

	if(fromId < 0)
	{
		throw DBExceptionSoft("Incorrect sender '" + message.from() + "'");
	}

	uint32_t toId = getUserId(message.to());

	if(toId < 0)
	{
		toId = _allId;
	}

	query("insert into messages(id, from_user_id, to_user_id, text, date) values(default, " + std::to_string(fromId) + ", " + std::to_string(toId) + ", '" + message.msg() + "', default)");
}

std::shared_ptr<Message>SQL::getMessage(const uint32_t lastId, const std::string &login)const
{
	const int32_t userId = getUserId(login);

	if(userId < 0)
	{
		throw DBExceptionSoft("Incorrect recipient '" + login + "'");
	}

	std::string strUserId = std::to_string(userId);

	MYSQL_ROW row = mysql_fetch_row(query("select text, from_user_id, to_user_id, date, id from messages where id > " + std::to_string(lastId) + " and (from_user_id = " + strUserId + " or to_user_id in (" + strUserId + ", " + _strAllId + ")) limit 1"));

	if(!row)
	{
		return nullptr;
	}

	const uint32_t fromId = atoi(row[1]), toId = atoi(row[2]);
	std::string from, to;

	if(!getLoginById(from, fromId))
	{
		from = std::string(row[1]);
	}
	if(!getLoginById(to, toId))
	{
		to = std::string(row[2]);
	}

	return std::make_shared<Message>(row[0], from, to, row[3], static_cast<uint32_t>(std::stoul((row[4]))));
}

SQL &SQL::operator=(SQL &&that)noexcept
{
	_mysql = that._mysql;
	_allId = that._allId;
	_strAllId = that._strAllId;
	that._mysql = nullptr;

	return *this;
}

SQLBuilder::SQLBuilder()noexcept:_host(str2char(DB_DEFAULT_HOST)),_userName(nullptr),_password(nullptr),_db(nullptr),_port(0),_socket(nullptr),_flag(0){}

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

	mysql_set_character_set(mysql, "utf8");

	return SQL(mysql);
}
