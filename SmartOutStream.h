#pragma once
#define byte unsigned char
#define BYTES unsigned char*
class SmartOutStream
{
public:
	SmartOutStream();
	BYTES buffer;
	int offset;
	void WriteByte(byte value);
	void WriteShort(short value);
	void WriteInt(int value);
	void WriteBytes(BYTES payload, int length);
	void WriteString(const wchar_t* str);
private:
	void AllocMemory(int length);
};

