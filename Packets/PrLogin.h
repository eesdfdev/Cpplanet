#pragma once
#include "Packet.h"
class PrLogin : public Packet {
public:
	PrLogin() : Packet(0x56EFE4A7) {}
	virtual void encode() {
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteShort(0);
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteString(L"eesdf");
		stream->WriteByte(0);
		stream->WriteShort(0);
		stream->WriteByte(0);
		stream->WriteInt(0);
		stream->WriteByte(0);
		stream->WriteInt(0);
		stream->WriteByte(0);
		stream->WriteByte(0);

		//sub_4290C0 Start
		stream->WriteInt(0); //array
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);

		//arrays
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);
		stream->WriteInt(0);

		stream->WriteInt(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0); //1 == encode int
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);

		stream->WriteInt(0); //array
		stream->WriteInt(0); //array
		stream->WriteInt(0);
		stream->WriteInt(0); //array
		stream->WriteInt(0); //array

		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0); //some flag?
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		stream->WriteByte(0);
		//end function

		stream->WriteInt(0);
	}
};