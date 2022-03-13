#include <cstdint>
#include <arpa/inet.h>
#include <unistd.h>
#include "send.h"
#include "rtype.h"

bool success(const int sockd)
{
	uint8_t buffer[sizeof(uint32_t)];
	read(sockd, buffer, sizeof(uint32_t));
	return static_cast<rtype>(ntohl(*reinterpret_cast<uint32_t*>(buffer))) == rtype::SUCCESS;
}

bool send(const int sockd, const uint8_t *data, const size_t size)
{
	uint8_t dataSize[2 * sizeof(uint32_t)];
	uint32_t *dataSize32 = reinterpret_cast<uint32_t*>(dataSize);

	*dataSize32 = htonl(static_cast<uint32_t>(rtype::SIZE));
	*(dataSize32 + 1) = htonl(static_cast<uint32_t>(size));
	write(sockd, dataSize, 2 * sizeof(uint32_t));

	if(success(sockd))
	{
		write(sockd, data, size);
		return true;
	}

	return false;
}
