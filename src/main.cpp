#include "client.h"
#include "server.h"

int main()
{
	Server *server = getServer();
	delete server;

	return 0;
}
