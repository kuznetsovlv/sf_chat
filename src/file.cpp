#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"

namespace fs = std::filesystem;

file_exception::file_exception(const fs::path &path)noexcept:_path(path)
{
}

const char *file_exception::what()const noexcept
{
	std::string str = "Can not open or create file ";
	str += _path;
	return  str.c_str();
}

File::File(const fs::path &path)
{
	if(fs::exists(path))
	{
		_file = std::fstream(path, std::ios::in | std::ios::app);
	}
	else
	{
		_file = std::fstream(path, std::ios::in | std::ios::app | std::ios::trunc);
	}

	if(!_file.is_open())
	{
		throw file_exception(path);
	}

	_file.seekg(std::ios_base::beg);
	_line_positions.push_back(_file.tellg());

	while(!_file.eof())
	{
		char c;
		_file >> c;
		if(c == 0xa)
		{
			_line_positions.push_back(_file.tellg());
		}
	}

	_file << "test";
}

File::~File()
{
	_file.close();
}

void File::output(const std::string &line)
{
	_file.seekg(std::ios_base::end);
	_line_positions.push_back(_file.tellg());
	_file << line;
}
