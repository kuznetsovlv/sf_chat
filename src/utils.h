#pragma once
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>
#include "message.h"
#include "rtype.h"
#include "user.h"

extern const uint16_t SERVER_PORT;

void now(std::string&);

void split(std::string*, const size_t, const char, const std::string&);

void join(const std::string*, const size_t, const char, std::string&);

uint8_t *toBytes(const Message&, size_t&);

uint8_t *toBytes(const User&, size_t&);

uint8_t *toBytes(const uint32_t, size_t&);

std::shared_ptr<Message> bytesToMessage(const uint8_t*);

std::shared_ptr<User> bytesToUser(const uint8_t*);

const uint32_t bytesToMessageId(const uint8_t*);

void addType(uint8_t*, const rtype);

const rtype getType(const uint8_t*);

char *str2char(const std::string&);

template <class T> void clear(T *pointer)
{
	if(pointer)
	{
		delete[] pointer;
	}
}
