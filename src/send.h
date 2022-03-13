#pragma once
#include <cstdint>
#include <unistd.h>

bool success(const int);

bool send(const int, const uint8_t*, const size_t);
