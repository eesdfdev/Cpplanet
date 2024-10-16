#pragma once
#include "Packet.h"
class PrWorldList : public Packet {
public:
	PrWorldList() : Packet(0x4128264E) {}
	virtual void encode() {
		stream->WriteInt(1);
		for (int i = 0; i < 1; i++) {
			stream->WriteShort(0);
			stream->WriteString(L"[Cpplanet]ÀÌ½ÃÇÁ");
			stream->WriteShort(0);
			stream->WriteByte(0);
			stream->WriteByte(0);
		}
	}
};