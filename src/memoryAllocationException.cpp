#include "memoryAllocationException.h"

const char *MemoryAllocationException::what()const noexcept
{
	return "Can not allocate memory";
}
