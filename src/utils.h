#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

void now(std::string&);

void split(std::string*, size_t, char, std::string&);

void join(std::string*, size_t, char, std::string&);
