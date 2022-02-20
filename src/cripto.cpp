#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <string>
#include "cripto.h"

const std::string CHARS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const size_t MIN_SALT_LENGTH = 5;
const size_t VARIANCE_SIZE_LENGTH = 5;

const size_t ONE_BLOCK_SIZE_BYTES = 64;
const size_t ONE_BLOCK_SIZE_UINTS = ONE_BLOCK_SIZE_BYTES / sizeof(uint32_t);
const size_t BLOCK_EXPEND_SIZE_UINTS = 320 / sizeof(uint32_t);

const size_t SHA1_HASH_LENGTH_BYTES = 20;
const size_t SHA1_HASH_LENGTH_UINTS = SHA1_HASH_LENGTH_BYTES / sizeof(uint32_t);

const size_t BYTE_SIZE = 8;

const uint32_t H[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

size_t rnd(size_t mod)
{
	static bool initiated = false;

	if(!initiated)
	{
		srand(time(nullptr));
		initiated = true;
	}

	return rand() % mod;
}

uint32_t cyrcle_shift_left(const uint32_t v, const size_t bit_count)
{
	return (v << bit_count | v >> (8 * sizeof(uint32_t) - bit_count));
}

uint32_t bring_to_human_view(const uint32_t v)
{
	return ((v & 0x000000FF) << 24) | ((v & 0x0000FF00) << 8) | ((v & 0x00FF0000) >> 8) | ((v & 0xFF000000) >> 24);
}

void salt(const size_t length, std::string &res)
{
	for(size_t i = 0; i < length; ++i)
	{
		res.push_back(CHARS[rnd(CHARS.size())]);
	}
}

void salt(std::string &res)
{
	res.clear();

	salt(MIN_SALT_LENGTH + rnd(VARIANCE_SIZE_LENGTH), res);
}

uint32_t *sha1(const int8_t *bytes, const size_t size)
{
	uint32_t A = H[0];
	uint32_t B = H[1];
	uint32_t C = H[2];
	uint32_t D = H[3];
	uint32_t E = H[4];

	uint32_t totalBlockCount = size / ONE_BLOCK_SIZE_BYTES;
	uint32_t needAdditionalBytes = ONE_BLOCK_SIZE_BYTES - (size - totalBlockCount * ONE_BLOCK_SIZE_BYTES);

	if(needAdditionalBytes < BYTE_SIZE)
	{
		totalBlockCount += 2;
		needAdditionalBytes += ONE_BLOCK_SIZE_BYTES;
	}
	else
	{
		totalBlockCount += 1;
	}

	const uint32_t extendedMessageSize = size + needAdditionalBytes;

	uint8_t * newBytes = new uint8_t[extendedMessageSize];

	memcpy(newBytes, bytes, size);

	newBytes[size] = 0x80;
	memset(newBytes + size + 1, 0, needAdditionalBytes - 1);


	uint32_t *ptr_to_size = reinterpret_cast<uint32_t*>(newBytes + extendedMessageSize - sizeof(uint32_t));
	*ptr_to_size = bring_to_human_view(size * BYTE_SIZE);

	uint32_t exp_block[BLOCK_EXPEND_SIZE_UINTS];

	for(size_t i = 0; i < totalBlockCount; ++i)
	{
		uint8_t *cur_p = newBytes + ONE_BLOCK_SIZE_BYTES * i;
		uint32_t *block = reinterpret_cast<uint32_t*>(cur_p);

		for(size_t j = 0; j < ONE_BLOCK_SIZE_UINTS; ++j)
		{
			exp_block[j] = bring_to_human_view(block[j]);
		}

		for(size_t j = ONE_BLOCK_SIZE_UINTS; j < BLOCK_EXPEND_SIZE_UINTS; ++j)
		{
			exp_block[j] = cyrcle_shift_left(exp_block[j -3] ^ exp_block[j - 8] ^ exp_block[j - 14] ^ exp_block[j - 16], 1);
		}

		uint32_t a = H[0];
		uint32_t b = H[1];
		uint32_t c = H[2];
		uint32_t d = H[3];
		uint32_t e = H[4];

		for(size_t j = 0; j < BLOCK_EXPEND_SIZE_UINTS; ++j)
		{
			uint32_t f, k;
			if(j < 20)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if(j < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if(j < 60)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = cyrcle_shift_left(a, 5) + f + e + k + exp_block[j];
			e = d;
			d = c;
			c = cyrcle_shift_left(b, 30);
			b = a;
			a = temp;
		}

		A += a;
		B += b;
		C += c;
		D += d;
		E += e;
	}

	uint32_t *res = new uint32_t[SHA1_HASH_LENGTH_UINTS];
	res[0] = A;
	res[1] = B;
	res[2] = C;
	res[3] = D;
	res[4] = E;

	delete[] newBytes;

	return res;
}

uint32_t *sha1(const std::string &str)
{
	return sha1(reinterpret_cast<const int8_t *>(str.c_str()), str.size());
}

void stringifyHash(const uint32_t *hash, std::string &res)
{
	std::stringstream stream;

	for(size_t i = 0; i < SHA1_HASH_LENGTH_UINTS; ++i)
	{
		stream << std::hex << *(hash + i);
	}

	res = stream.str();
}

void sha1String(const std::string &str, std::string &res)
{
	const uint32_t *hash = sha1(str);

	stringifyHash(hash, res);

	delete[] hash;
}
