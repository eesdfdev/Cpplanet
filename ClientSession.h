#pragma once
#include <winsock.h>
#define BYTES unsigned char*
class ClientSession {
public:
	ClientSession(SOCKET socket);
	SOCKET sock;
	void Send(BYTES buffer, int len);
private:
	void SendPatchData();
	void ReceivingThread();
	void OnRawPacket(BYTES buffer);
	void Disconnect();
};