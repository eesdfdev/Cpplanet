#pragma once
#include "Packet.h"
class PrSyncDate : public Packet {
public:
	PrSyncDate() : Packet(0x38C0ACD8) {}
	virtual void encode() {
		stream->WriteInt(1); //unknown
	}
};