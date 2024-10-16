#pragma once
#include "Packets/Packet.h"
#include "Packets/PrSyncTick.h"
#include "Packets/PrSyncDate.h"
class PacketFactory {
public:
	static Packet* GetServerPacket(unsigned int rttiValue) {
		Packet* packet = nullptr;
		switch (rttiValue) {
		case 0x764F67D9: //PqSyncTick
			packet = new PrSyncTick();
			break;
		case 0x6C388FD7:
			packet = new PrSyncDate();
			break;
		}
		return packet;
	}
};