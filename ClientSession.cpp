#include "ClientSession.h"
#include "Stream/SmartOutStream.h"
#include <thread>
#include <iostream>
#include "Logger.h"

#include "Packets/PcFirstMessage.h"
#include "PacketFactory.h"

#include <sstream>
#include <iomanip>
std::wstring hexStr(const uint8_t* data, int len)
{
	std::wstringstream ss;
	ss << std::hex;

	for (int i(0); i < len; ++i)
		ss << std::setw(2) << std::setfill(L'0') << (int)data[i];

	return ss.str();
}

ClientSession::ClientSession(SOCKET socket) {
	sock = socket;
	SendPatchData();
	std::thread receiveThread(&ClientSession::ReceivingThread, this);
	receiveThread.join();
}
void ClientSession::Disconnect() {
	closesocket(sock);
}
void ClientSession::SendPatchData() {
	Packet* packet = new PcFirstMessage();
	packet->encode();
	Send(packet->stream->buffer, packet->stream->offset);
}
void ClientSession::ReceivingThread() {
	while (1) {
		int length = 0;
		int received = recv(sock, (char*)&length, 4, 0);
		if (received == 4) { //암호화 처리 해줘야 하는데 암호화 비활성화되서 필요 없음.
			Logger::Info(L"New Packet");
			Logger::Info(L" 패킷 길이 %d", length);
			BYTES buffer = (BYTES)malloc(length);
			if (length > 0 && length < 0xFFFF) {
				received = recv(sock, (char*)buffer, length, 0);
				if (received != 0) {
					OnRawPacket(buffer, length);
				}
				else {
					Logger::Warn(L" 올바른 패킷을 받지 못했습니다.");
					Disconnect();
				}
			}
			else {
				Logger::Warn(L" 패킷 길이가 %d 이였습니다", length);
				Disconnect();
			}
		}
		else {
			Logger::Info(L" 연결이 종료되었습니다.");
			Disconnect();
			return;
		}
	}
}
void ClientSession::OnRawPacket(BYTES buffer, int length) {
	int rttiValue = *(int*)buffer;
	Logger::Info(L" 패킷 0x%08x을 받았습니다.", rttiValue);
	Logger::Info(L" 패킷 Payload : %s", hexStr(buffer, length));

	//skipping Client packet Rtti
	SmartInStream* InStream = new SmartInStream((buffer + 4), length - 4); 
	Packet* packet = nullptr;
	packet = PacketFactory::GetServerPacket(rttiValue);
	if (packet != nullptr) {
		packet->decode(InStream);
		packet->encode();
		Send(packet->stream->buffer, packet->stream->offset);
	}
}
void ClientSession::Send(BYTES buffer, int len) {
	Logger::Info(L"New Packet");
	Logger::Info(L" 패킷 0x%08x을 보냈습니다.", *( int* ) buffer);
	SmartOutStream* outStream = new SmartOutStream();
	outStream->WriteInt(len);
	outStream->WriteBytes(buffer, len);
	if (send(sock, (char*)outStream->buffer, outStream->offset, 0) == -1) {
		Logger::Warn(L"ClientSession::Send 에러 코드 : %d", WSAGetLastError());
	}
}