#pragma once
#include <winsock.h>
#define BYTE unsigned char
#define BYTES BYTE*
class ClientSession {
public:
	ClientSession(SOCKET socket);
	SOCKET sock;
	void Send(BYTES buffer, int len);
private:
	void SendPatchData();
	void ReceivingThread();
	void OnRawPacket(BYTES buffer, int length);
	void Disconnect();
};