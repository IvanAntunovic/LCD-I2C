/*
 * LCD.cpp
 *
 * Created: 5/20/2017 5:53:27 PM
 *  Author: fairenough
 */ 

#ifndef _LCD_H_
#define _LCD_H_

#include "I2CAdapter.h"
#include "LCDTransmitter.h"
#include "LCDTypes.h"
#include <string.h>
#include <util/delay.h>

class LCDTransmitter;

class LCD
{
	private:
		LCDTransmitter* lcdTransmitter;
		uint8_t numLines;
		uint8_t numColumns;
		
	public:
	    LCD(I2CAdapter* i2cAdapter);
		void open(uint8_t numLines, uint8_t numColumns);
		int8_t writeByte(uint8_t byte);
		int8_t writeBytes(uint8_t* buffer, uint8_t length);
		int8_t writeString(const char* text);
		int8_t writeCommand(uint8_t command);
		int8_t setCursor(uint8_t x, uint8_t y);
		int8_t display(uint8_t ledOnOff);
		int8_t clearScreen(void);
		int8_t home(void);
		
	private:
		void checkIfBusy();
};

#endif
