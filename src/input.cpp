#include <iostream>
#include <limits>
#include <string>
#include "input.h"

void ignore()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isLogin(const std::string &str)
{
	for(char c: str)
	{
		if(c == '@' || c == ':' || c == ' ' || c == '\t')
		{
			return false;
		}
	}
	return true;
}

void cutTo(std::string &str, const size_t maxSize)
{
	if(str.size() > maxSize)
	{
		str.erase(maxSize);
	}
}
