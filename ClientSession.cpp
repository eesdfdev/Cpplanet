#include "ClientSession.h"
#include "SmartOutStream.h"
#include <thread>
#include <iostream>

#include "Packet.h"
#include "PrSyncTick.h"
#include "PrSyncDate.h"

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
	SmartOutStream* stream = new SmartOutStream();
	stream->WriteInt(0x7191CA); //PcFirstMessage rttiValue

	//I know Hard-Coded consts are bad
	stream->WriteInt(1);
	stream->WriteShort(1003);
	stream->WriteByte(118);
	stream->WriteShort(680);
	stream->WriteString(L"TestURL");
	stream->WriteInt(0); //server key
	stream->WriteInt(0); //server key
	stream->WriteBytes((BYTES)calloc(32, sizeof(BYTE)), 32);
	Send(stream->buffer, stream->offset);
}
void ClientSession::ReceivingThread() {
	while (1) {
		int length = 0;
		int received = recv(sock, (char*)&length, 4, 0);
		if (received == 4) { //��ȣȭ ó�� ����� �ϴµ� ��ȣȭ ��Ȱ��ȭ�Ǽ� �ʿ� ����.
			std::cout << "New Packet" << std::endl;
			std::cout << " ��Ŷ ���� : " << length << std::endl;
			BYTES buffer = (BYTES)malloc(length);
			if (length > 0 && length < 0xFFFF) {
				received = recv(sock, (char*)buffer, length, 0);
				if (received != 0) {
					OnRawPacket(buffer, length);
				}
				else {
					std::cout << " �ùٸ� ��Ŷ�� ���� ���߽��ϴ�." << std::endl;
				}
			}
			else {
				std::cout << " ��Ŷ ���̰� " << length << "�̿����ϴ�." << std::endl; //�߸��� ��Ŷ�� receive���� ���ɼ��� ����.
			}
		}
		else {
			std::cout << " ������ ����Ǿ����ϴ�." << std::endl;
			Disconnect();
			return;
		}
	}
}
void ClientSession::OnRawPacket(BYTES buffer, int length) {
	int rttiValue = *(int*)buffer;
	std::cout << " ��Ŷ " << std::hex << rttiValue << "�� �޾ҽ��ϴ�." << std::endl;
	std::cout << " ��Ŷ Payload : " << hexStr(buffer, length) << std::endl;
	//���� ��Ŷ�� Return���ִ� function ���� �ʿ�
	Packet* packet = nullptr;
	switch (rttiValue) {
	case 0x764F67D9: //PqSyncTick
		packet = new PrSyncTick();
		break;
	case 0x6C388FD7:
		packet = new PrSyncDate();
		break;
	}
	if (packet != nullptr) {
		packet->encode();
		Send(packet->stream->buffer, packet->stream->offset);
	}
}
void ClientSession::Send(BYTES buffer, int len) {
	std::cout << "New Packet" << std::endl;
	std::cout << " ��Ŷ " << std::hex << *(int*)buffer << "�� ���½��ϴ�." << std::endl;
	SmartOutStream* outStream = new SmartOutStream();
	outStream->WriteInt(len);
	outStream->WriteBytes(buffer, len);
	if (send(sock, (char*)outStream->buffer, outStream->offset, 0) == -1) {
		std::cout << "ClientSession::Send ���� �ڵ� : " << WSAGetLastError() << std::endl;
	}
}