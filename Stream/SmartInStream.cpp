#include "SmartInStream.h"
SmartInStream::SmartInStream(BYTES payload, int length) {
	buffer = payload;
	this->length = length;
	offset = 0;
}
bool SmartInStream::checkForLength(int len) {
	if (offset + len <= length) {
		return true;
	}
	return false;
}
BYTE SmartInStream::ReadByte() {
	if(checkForLength(1)){
		return buffer[ offset++ ];
	}
	return 0xFF;
}
