#pragma once
#include "Packets/Packet.h"
#include "Packets/PrSyncTick.h"
#include "Packets/PrSyncDate.h"
#include "Packets/PrLogin.h"
#include "Packets/PrWorldList.h"
class PacketFactory {
public:
	static Packet* GetServerPacket(unsigned int rttiValue) {
		Packet* packet = nullptr;
		switch (rttiValue) {
		case 0x764F67D9: //PqSyncTick
			packet = new PrSyncTick();
			break;
		case 0x6C388FD7: //PqSyncDate
			packet = new PrSyncDate();
			break;
		case 0x40C38368: //PqLogin
			packet = new PrLogin();
			break;
		case 0xfd1640f: //PqWorldList
			packet = new PrWorldList();
			break;
		}
		return packet;
	}
};