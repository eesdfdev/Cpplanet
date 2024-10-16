#include <iostream>
#include <Windows.h>
#include "ServerSock.h"

int main() {
	ShellExecute(NULL, "open", "https://discord.gg/bw67XNE2EH", NULL, NULL, SW_SHOWNORMAL);

	
	ServerSock* socket = new ServerSock();
	socket->Run();
	return 0;
}