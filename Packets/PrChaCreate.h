#pragma once
#include "Packet.h"
#include <iostream>

class PrChaCreate : public Packet {
public:
	PrChaCreate() : Packet(0x45DC2136) {};
	virtual void encode() {
		stream->WriteInt(0);

		stream->WriteInt(0);
		stream->WriteShort(0);
		stream->WriteString(L"이시프");
		stream->WriteShort(0);
		stream->WriteShort(0);
		stream->WriteByte(0);
		stream->WriteShort(0);
		stream->WriteShort(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteInt(0);
		stream->WriteBytes(( BYTES ) calloc(0x10, sizeof(BYTE)), 0x10);

		stream->WriteBytes(( BYTES ) calloc(30, sizeof(BYTE)), 30);
	}
};