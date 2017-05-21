/*
 * LCDTransmitter.cpp
 *
 * Created: 5/21/2017 8:23:53 AM
 *  Author: fairenough
 */ 
#ifndef _LCD_TRANSMITTER_H_
#define _LCD_TRANSMITTER_H_

#include "Writable.h"
#include "I2CAdapter.h"
#include "LCDTypes.h"

class LCDTransmitter : public Writable
{
	private:
		I2CAdapter* i2cAdapter;
		uint8_t adapterOutputPort;

	public:
		LCDTransmitter(I2CAdapter* i2cAdapter);
		int8_t writeBytes(uint8_t* buffer, uint8_t length);
		int8_t writeByte(uint8_t byte, const uint8_t MODE);
		int8_t writeCommand(uint8_t command);
		int8_t setCursor(uint8_t x, uint8_t y);
		int8_t display(uint8_t ledOnOff);
		
	private:
		int8_t waitIfBusy();
		void setWritePinBytes(uint8_t* sequenceBytes, uint8_t startIndex);
};

#endif