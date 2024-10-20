#pragma once
#include "Packet.h"
#include <iostream>

class PrChaList : public Packet {
public:
	PrChaList() : Packet(0x65EDE578) {};
	virtual void encode() {
		stream->WriteInt(0);
		stream->WriteInt(1);
		for ( int i = 0; i < 1; i++ ) {
			stream->WriteInt(1);
			stream->WriteShort(1);
			stream->WriteString(L"이시프");
			stream->WriteShort(1);
			stream->WriteShort(1);
			stream->WriteByte(1);
			stream->WriteShort(1);
			stream->WriteShort(1);
			stream->WriteByte(1);
			stream->WriteByte(1);
			stream->WriteInt(1);
			stream->WriteBytes(( BYTES ) calloc(0x10, sizeof(BYTE)), 0x10);

			stream->WriteBytes(( BYTES ) calloc(30, sizeof(BYTE)), 30);
		}
	}
};