#pragma once
#include "SmartOutStream.h"
class Packet
{
public:
	Packet(unsigned int rttiValue) {
		stream = new SmartOutStream();
		stream->WriteUInt(rttiValue);
	};
	virtual void encode() {};
	SmartOutStream* stream;
};

