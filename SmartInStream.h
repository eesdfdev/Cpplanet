#pragma once
#define BYTES unsigned char*
class SmartInStream
{
public:
	SmartInStream();
	BYTES buffer;
private:
	int offset;
};

