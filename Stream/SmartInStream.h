#pragma once
#define BYTE unsigned char
#define BYTES BYTE*
class SmartInStream
{
public:
	SmartInStream(BYTES payload, int length);
	BYTE ReadByte();
	BYTES buffer;
private:
	int offset;
	int length;
	bool checkForLength(int len);
};
