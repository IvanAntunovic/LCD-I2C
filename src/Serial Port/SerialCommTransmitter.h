#pragma once
#ifndef  _SERIALCOMMTRANSMITTER_H_
#define  _SERIALCOMMTRANSMITTER_H_

#include "CircularQueue.h"
#include "Writable.h"
#include <stdlib.h>

#define SERIAL_OK   0
#define SERIAL_NOK -1

class SerialCommTransmitter : public Writable
{
	private:
		CircularQueue txQueue;
		uint8_t portSelected;

	public:
		SerialCommTransmitter(uint8_t portSelected);
		int8_t writeByte(uint8_t byte);
		int8_t writeBytes(uint8_t* bytes, uint8_t length);
		uint8_t write(const char* string);
		uint8_t write(int value);
		uint8_t availableForWrite();
		friend class SerialPort;
};

#endif // !_SERIALCOMMTRANSMITTER_H_




