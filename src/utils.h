#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

const std::string now();

void split(std::string*, size_t, char, std::string&);

void join(std::string*, size_t, char, std::string&);
