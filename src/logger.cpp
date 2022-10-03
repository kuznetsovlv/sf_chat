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
