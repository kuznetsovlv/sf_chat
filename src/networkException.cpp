#include "networkException.h"

NetworkException::NetworkException(const char *what):_what(what)
{
}

const char *NetworkException::what()const noexcept
{
	return _what;
}
