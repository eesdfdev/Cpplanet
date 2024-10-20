#pragma once
#include "Stream/SmartOutStream.h"
#include "Stream/SmartInStream.h"
class Packet
{
public:
	Packet(unsigned int rttiValue) {
		stream = new SmartOutStream();
		stream->WriteUInt(rttiValue);
	};
	virtual void encode() {};
	virtual void decode(SmartInStream* InStream) {};
	SmartOutStream* stream;
};

