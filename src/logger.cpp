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

	if(!_path.empty() && _file.is_open())
	{
		_file.seekg(_pos, std::ios_base::beg);
		while(!_file.eof())
		{
			char c = _file.get();

			if(c == 0xa && !_file.eof())
			{
				_pos = _file.tellg();
				break;
			}
			else if(c == -1 || _file.eof())
			{
				break;
			}

			str += c;
		}
	}

	_file.clear();

	_mutex.unlock_shared();
}

void Logger::output(const std::string &str)
{
	const std::lock_guard<std::shared_mutex> lock(_mutex);
	if(!_path.empty() && _file.is_open())
	{
		_file << str << std::endl;
	}
}

void Logger::open(const std::filesystem::path &path)
{
	if(_path == path)
	{
		return;
	}

	close();

	const std::lock_guard<std::shared_mutex> lock(_mutex);
	_path = path;
	_file.open(path, std::ios::in | std::ios::app);

	if(!_file.is_open())
	{
		throw file_exception(_path);
	}

	_file.seekg(std::ios_base::beg);
	_pos = _file.tellg();
	_file.clear();
}

void Logger::close()
{
	const std::lock_guard<std::shared_mutex> lock(_mutex);

	if(!_path.empty())
	{
		_path.clear();
	}

	if(_file.is_open())
	{
		_file.close();
	}
}
