#include <iostream>
#include "rtype.h"

int main()
{
	std::cout << sizeof(rtype) << " " << sizeof(rtype::EMPTY) << std::endl;
	std::cout << sizeof(size_t) << std::endl;
	return 0;
}
