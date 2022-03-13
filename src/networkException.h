#pragma once
#include <exception>

class NetworkException final: public std::exception
{
	private:
	const char *_what;

	public:
	explicit NetworkException(const char*);

	virtual const char *what()const noexcept override;
};
