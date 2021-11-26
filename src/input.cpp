#include <iostream>
#include <ios>
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
