#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include "logger.h"

file_exception::file_exception(const std::filesystem::path &path)noexcept:_path(path)
{
}

const char *file_exception::what()const noexcept
{
	std::string str = "Can not open or create file ";
	str += _path;
	return str.c_str();
}

Logger::Logger(const std::filesystem::path &path):_path(path)
{
	init();
}

Logger::~Logger()
{
	_file.close();
}

void Logger::init()
{
	_file = std::fstream(_path, std::ios::in | std::ios::app);

	if(!_file.is_open())
	{
		throw file_exception(_path);
	}
}

void Logger::input(std::string &str)
{
	str.clear();

	_mutex.lock_shared();

	while(!_file.eof())
	{
		char c;

		_file.get(c);

		if(c == 0xa)
		{
			break;
		}

		str += c;
	}

	_mutex.unlock_shared();
}

void Logger::output(const std::string &str)
{
	_mutex.lock();
	_file << str << std::endl;
	_mutex.unlock();
}

void Logger::setPath(const std::filesystem::path &path)
{
	_mutex.lock();

	if(_file.is_open())
	{
		_file.close();
	}

	_path = path;

	init();

	_mutex.unlock();
}
