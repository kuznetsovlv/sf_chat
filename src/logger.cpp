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

Logger::Logger()noexcept
{
}

Logger::~Logger()
{
	close();
}

void Logger::input(std::string &str)
{
	str.clear();

	_mutex.lock_shared();

	if(_path.empty() || !_file.is_open())
	{
		return;
	}

	while(!_file.eof())
	{
		char c = _file.get();

		if(c == 0xa || _file.eof())
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
	if(!_path.empty() && _file.is_open())
	{
		_file.clear();
		_file << str << std::endl;
	}
	_mutex.unlock();
}

void Logger::open(const std::filesystem::path &path)
{
	if(_path == path)
	{
		return;
	}

	close();

	_mutex.lock();
	_path = path;
	_file.open(path, std::ios::in | std::ios::app);

	if(!_file.is_open())
	{
		throw file_exception(_path);
	}

	_file.clear();
	_mutex.unlock();
}

void Logger::close()
{
	_mutex.lock();

	if(!_path.empty())
	{
		_path.clear();
	}

	if(_file.is_open())
	{
		_file.close();
	}

	_mutex.unlock();
}
