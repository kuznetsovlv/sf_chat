#include "client.h"
#include "server.h"

Client::Client(Server *server)noexcept:_server(server)
{
}

Client::~Client()noexcept
{
	deleteServer();
}
