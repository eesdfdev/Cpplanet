#pragma once
#include "Packet.h"
#include <iostream>

class PrChaList : public Packet {
public:
	PrChaList() : Packet(0x65EDE578) {};
	virtual void encode() {
		stream->WriteInt(0);
		stream->WriteInt(0);
	}
};