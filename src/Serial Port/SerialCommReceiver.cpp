#include "SerialCommReceiver.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif

SerialCommReceiver::SerialCommReceiver()
{
	//this->rxBinarySemaphore = xSemaphoreCreateBinary();
	//
	//if (this->rxBinarySemaphore != NULL)
	//{
		////Handle error
	//}
}

unsigned char SerialCommReceiver::available()
{
	return rxQueue.getAvailableItems();
}

int8_t SerialCommReceiver::readByte(uint8_t* byte)
{
	//if ( xSemaphoreTake(this->rxBinarySemaphore, 0) == pdPASS)
	{
		if (!rxQueue.isEmpty())
		{
			rxQueue.dequeue(byte);
			return SERIAL_OK;
		}
	}
	
	return SERIAL_NOK;
}

int8_t SerialCommReceiver::readBytes(uint8_t* buffer, uint8_t length)
{
	uint8_t bytesRead = 0;

	for (uint8_t i = 0; i < length && this->rxQueue.isAvailable(); ++i)
	{
		if(readByte(buffer) == SERIAL_OK)
		{
			buffer++;
			bytesRead++;
		}
	}
	
	return bytesRead;
}
