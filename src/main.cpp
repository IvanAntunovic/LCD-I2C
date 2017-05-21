/*
 * LCD_I2C_4bit.cpp
 *
 * Created: 5/20/2017 11:51:13 AM
 * Author : fairenough
 */ 

#define PCF8574A_ADDRESS	0x3F
#include <avr/io.h>
#include <string.h>
#include "LCD.h"
#include "I2CAdapter.h"
#include "LCDTransmitter.h"
#include "SerialPort.h"
#include "I2CPort.h"
#include "util/delay.h"

I2CPort i2cPort;
I2CAdapter i2cAdapter(&i2cPort);
LCDTransmitter lcdTransmitter(&i2cAdapter);
LCD lcd(&i2cAdapter);

int main(void)
{
	const char* data = "hello";
	int8_t retVal;
	SerialPort serialPort;
	SerialPort serialPortOne;
	serialPort.open(9600, 0);
	serialPortOne.open(9600, 1);

	uint8_t aChar;
	uint8_t buffer[] = {'A', 'B'};
	int index = 0;
	

	lcd.writeCommand(LCD_DISP_ON_CURSOR_BLINK);
	lcd.writeCommand(LCD_CLR);
	
	
	while (1)
	{		

		if (serialPort.available())
		{
			serialPort.readBytes(&aChar, 1);
			serialPort.writeBytes(&aChar, 1);
			if (aChar == 'D')
			{
				
				lcd.writeCommand(LCD_MOVE_CURSOR_RIGHT);
			}
			if (aChar == 'A')
			{
				
				lcd.writeCommand(LCD_MOVE_CURSOR_LEFT);
			}
			if (aChar == 'W')
			{
				lcd.display(LCD_DISP_ON);
			}
			lcd.writeByte(aChar);
		}
	}
}

