#include "memory_allocation_exception.h"

const char *MemoryAllocationException::what()const noexcept
{
	return "Can not allocate memory";
}
