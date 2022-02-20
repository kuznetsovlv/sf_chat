#pragma once

void salt(const size_t, std::string&);
void salt(std::string&);

uint32_t *sha1(const int8_t*, const size_t);
uint32_t *sha1(const std::string&);

void stringifyHash(const uint32_t*, std::string&);
void sha1String(const std::string&, std::string&);
