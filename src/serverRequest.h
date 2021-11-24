#pragma once

class ServerRequest
{
	public:
	virtual ~ServerRequest() = 0;
};

class NewMessageServerRequest final: public ServerRequest
{
};
