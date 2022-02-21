#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>

void now(std::string&);

void split(std::string*, const size_t, const char, const std::string&);

void join(const std::string*, const size_t, const char, std::string&);
