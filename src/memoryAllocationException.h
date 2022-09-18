#pragma once
#include <exception>

class MemoryAllocationException final: public std::exception
{
	public:
	virtual const char *what()const noexcept override;
};
