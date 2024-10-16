#pragma once
#define BYTE unsigned char
#define BYTES BYTE*
class SmartInStream
{
public:
	SmartInStream();
	BYTES buffer;
private:
	int offset;
};

