#include "SmartOutStream.h"
#include <iostream>
SmartOutStream::SmartOutStream() {
	buffer = nullptr;
	offset = 0;
}
void SmartOutStream::AllocMemory(int length) {
	if (buffer != nullptr) {
		BYTES tempBuf = (BYTES)malloc(offset + length);
		if (tempBuf == nullptr) {
			std::cout << "Malloc returned nullptr in SmartOutStream::AllocMemory" << std::endl;
			return;
		}
		memcpy(tempBuf, buffer, offset);
		free(buffer);
		buffer = tempBuf;
		return;
	}
	buffer = (BYTES)malloc(length);
}
void SmartOutStream::WriteByte(byte value) {
	AllocMemory(1);
	*(byte*)(buffer + offset) = value;
	offset += 1;
}
void SmartOutStream::WriteShort(short value) {
	AllocMemory(2);
	*(short*)(buffer + offset) = value;
	offset += 2;
}
void SmartOutStream::WriteInt(int value) {
	AllocMemory(4);
	*(int*)(buffer + offset) = value;
	offset += 4;
}
void SmartOutStream::WriteBytes(BYTES value, int length) {
	AllocMemory(length);
	memcpy((buffer + offset), value, length);
	offset += length;
}
void SmartOutStream::WriteString(const wchar_t* str) {
	int stringLength = wcslen(str);
	WriteInt(stringLength);
	AllocMemory(stringLength);
	WriteBytes((BYTES)str, stringLength);
	offset += stringLength;
}