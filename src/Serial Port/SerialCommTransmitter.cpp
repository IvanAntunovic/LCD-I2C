#include "SerialCommTransmitter.h"
#include <avr/interrupt.h>

//#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
//#endif

SerialCommTransmitter::SerialCommTransmitter(uint8_t _portSelected): portSelected (_portSelected){};

uint8_t SerialCommTransmitter::availableForWrite()
{
	return BUFFER_SIZE - txQueue.getAvailableItems();
}

int8_t SerialCommTransmitter::writeByte(unsigned char byte)
{
	// wait until queue is empty
	//unsigned char tempTail = (txQueue.tail + 1) & BUFFER_MASK;b
	while (txQueue.isFull());

	// check if byte is successfully pushed into queue
	if (txQueue.enqueue(byte))
	{
		// Check which port is selected
		// enable USART Data Register Empty Interrupt
		if (this->portSelected == 0)
		{
			UCSR0B |= (1 << UDRIE0); 
		}
		else if (this->portSelected == 1)
		{
			UCSR1B |= (1 << UDRIE1); 
		}
			
		return SERIAL_OK;
	}
	return SERIAL_NOK;
}

int8_t SerialCommTransmitter::writeBytes(unsigned char* bytes, unsigned char length)
{
	uint8_t bytesWrittenCnt = 0;
	
	for (uint8_t i = 0; i < length; i++)
	{
		if (writeByte(bytes[bytesWrittenCnt]) != SERIAL_NOK)
			bytesWrittenCnt++;
	}

	return bytesWrittenCnt;
}

uint8_t SerialCommTransmitter::write(const char* string)
{
	uint8_t bytesWritten;
	
	for (bytesWritten = 0; *string; bytesWritten++)
	{
		writeByte(*string++);
	}
	return bytesWritten;
}

uint8_t SerialCommTransmitter::write(int value)
{
	uint8_t numberOfDigits;
	uint8_t buffer[10];
	int tempValue;
	
	tempValue = value;
	for (numberOfDigits = 0; tempValue != 0; numberOfDigits++)
	{
		tempValue = tempValue / 10;
	}
	itoa(value, (char*)buffer, 10);
	return writeBytes(buffer, numberOfDigits);
}