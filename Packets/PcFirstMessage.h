#pragma once
#include "Packet.h"
#include <iostream>

class PcFirstMessage : public Packet {
public:
	PcFirstMessage() : Packet(0x7191CA) {};
	virtual void encode() {
		//I know Hard-Coded consts are bad
		stream->WriteInt(1);
		stream->WriteShort(1003);
		stream->WriteByte(118);
		stream->WriteShort(680);
		stream->WriteString(L"TestURL");
		stream->WriteInt(0); //server key
		stream->WriteInt(0); //server key
		stream->WriteBytes((BYTES)calloc(32, sizeof(BYTE)), 32);
	}
};