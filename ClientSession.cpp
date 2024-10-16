#include "ClientSession.h"
#include "SmartOutStream.h"
#include <thread>
#include <iostream>

#include "Packets/PcFirstMessage.h"
#include "PacketFactory.h"

#include <sstream>
#include <iomanip>
std::string hexStr(const uint8_t* data, int len)
{
	std::stringstream ss;
	ss << std::hex;

	for (int i(0); i < len; ++i)
		ss << std::setw(2) << std::setfill('0') << (int)data[i];

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
			std::cout << "New Packet" << std::endl;
			std::cout << " 패킷 길이 : " << length << std::endl;
			BYTES buffer = (BYTES)malloc(length);
			if (length > 0 && length < 0xFFFF) {
				received = recv(sock, (char*)buffer, length, 0);
				if (received != 0) {
					OnRawPacket(buffer, length);
				}
				else {
					std::cout << " 올바른 패킷을 받지 못했습니다." << std::endl;
				}
			}
			else {
				std::cout << " 패킷 길이가 " << length << "이였습니다." << std::endl; //잘못된 패킷을 receive했을 가능성이 높음.
			}
		}
		else {
			std::cout << " 연결이 종료되었습니다." << std::endl;
			Disconnect();
			return;
		}
	}
}
void ClientSession::OnRawPacket(BYTES buffer, int length) {
	int rttiValue = *(int*)buffer;
	std::cout << " 패킷 " << std::hex << rttiValue << "을 받았습니다." << std::endl;
	std::cout << " 패킷 Payload : " << hexStr(buffer, length) << std::endl;

	Packet* packet = nullptr;
	packet = PacketFactory::GetServerPacket(rttiValue);
	if (packet != nullptr) {
		packet->encode();
		Send(packet->stream->buffer, packet->stream->offset);
	}
}
void ClientSession::Send(BYTES buffer, int len) {
	std::cout << "New Packet" << std::endl;
	std::cout << " 패킷 " << std::hex << *(int*)buffer << "을 보냈습니다." << std::endl;
	SmartOutStream* outStream = new SmartOutStream();
	outStream->WriteInt(len);
	outStream->WriteBytes(buffer, len);
	if (send(sock, (char*)outStream->buffer, outStream->offset, 0) == -1) {
		std::cout << "ClientSession::Send 에러 코드 : " << WSAGetLastError() << std::endl;
	}
}