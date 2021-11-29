#pragma once
#include <string>

class Response
{
	private:
	const bool _success;
	const std::string _message;

	public:
	Response(bool,std::string)noexcept;

	virtual bool success()const noexcept final ;
	virtual const std::string &message()const noexcept final ;
};
