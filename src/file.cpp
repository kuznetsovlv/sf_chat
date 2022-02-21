#include <iostream>
#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"

file_exception::file_exception(const std::filesystem::path &path)noexcept:_path(path)
{
}

const char *file_exception::what()const noexcept
{
	std::string str = "Can not open or create file ";
	str += _path;
	return  str.c_str();
}

File::File(const std::filesystem::path &path):_path(path)
{
	_file = std::fstream(path, std::ios::in | std::ios::app);

	if(!_file.is_open())
	{
		throw file_exception(path);
	}

	_file.seekg(std::ios_base::beg);
	_line_positions.push_back(_file.tellg());

	while(!_file.eof())
	{
		char c;
		_file.get(c);
		if(c == 0xa && !_file.eof())
		{
			_line_positions.push_back(_file.tellg());
		}
	}

	_file.clear();
}

File::~File()
{
	_file.close();
}

std::string File::getLine(const size_t index)
{
	std::string res;

	if(index < lines())
	{
		_file.seekg(_line_positions[index], std::ios_base::beg);
		while(true)
		{
			char c;
			_file.get(c);
			if(c == 0xa)
			{
				return res;
			}
			res += c;
		}
	}

	return res;
}

void File::output(const std::string &line)
{
	_file << line << std::endl;
	_file.seekg(0, std::ios_base::end);
	_line_positions.push_back(_file.tellg());
}

size_t File::lines()const noexcept
{
	return _line_positions.size() - 1;
}

std::uintmax_t File::bytes()const
{
	return std::filesystem::file_size(_path);
}
