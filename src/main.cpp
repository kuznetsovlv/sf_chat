#include <iostream>
#include "user.h"

int main()
{
	std::cout << ALL << std::endl;
	User user;

	std::cout << user.getLogin() << std::endl;

	User user2("userLogin", "userName", "userPassword");

	std::cout << user2.getLogin() << user2.getFullName() << user2.getPassword() << std::endl;
	std::cout << user.getLogin() << user.getFullName() << user.getPassword() << std::endl;

	return 0;
}
