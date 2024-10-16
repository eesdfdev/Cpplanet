#pragma once
#include <winsock.h>
class ServerSock {
public:
	ServerSock();
	SOCKET sock;
	SOCKADDR_IN sockaddr;
	void Run();
};