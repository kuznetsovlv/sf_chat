#include <string>
#include "response.h"

Response::Response(bool success, std::string message)noexcept:_success(success),_message(message)
{
}

bool Response::success()const noexcept
{
	return _success;
}

const std::string &Response::message()const noexcept
{
	return _message;
}
