#pragma once
#include "Packet.h"
#include <iostream>

class PrUserPin2Check : public Packet {
public:
	PrUserPin2Check() : Packet(0x10215E5E) {}
	virtual void encode() {
		stream->WriteBytes(( BYTES ) calloc(12, sizeof(BYTE)), 12);
	}
};