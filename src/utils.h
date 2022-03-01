#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>
#include "message.h"
#include "rtype.h"
#include "user.h"

void now(std::string&);

void split(std::string*, const size_t, const char, const std::string&);

void join(const std::string*, const size_t, const char, std::string&);

uint8_t *toBytes(const uint32_t, const Message&, size_t&);

uint8_t *toBytes(const uint32_t, const User&, size_t&);

std::shared_ptr<Message> fromBytes(const uint8_t*);

std::shared_ptr<User> fromBytes(const uint8_t*);

void addType(uint8_t*, const rtype);
