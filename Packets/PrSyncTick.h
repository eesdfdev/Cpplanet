#pragma once
#include "Packet.h"
class PrSyncTick : public Packet {
public:
	PrSyncTick() : Packet(0x496925DA) {}
	virtual void encode() {
		stream->WriteInt(0); //TickCount64
		stream->WriteInt(0);
	}
};