/*
 * LCDTransmitter.cpp
 *
 * Created: 5/20/2017 6:07:03 PM
 *  Author: fairenough
 */ 
#include "LCD.h"

LCD::LCD(I2CAdapter* i2cAdapter)
{
	this->lcdTransmitter = new LCDTransmitter(i2cAdapter);
	
	this->writeCommand(LCD_FUNCTION_4BIT_2LINES);
	this->writeCommand(LCD_CLR);
	this->writeCommand(LCD_MOVE_CURSOR_LEFT);
	this->writeCommand(LCD_FORCE_CURSOR_FIRST_LINE);
	this->writeCommand(LCD_DISP_ON_CURSOR);
	this->setCursor(0, 0);

	_delay_ms(16000);        /* wait 16ms or more after power-on       */

		
	/* from now the LCD only accepts 4 bit I/O, we can use lcd_command() */

	this->writeCommand(LCD_FUNCTION_4BIT_1LINE);      /* function set: display lines  */

	this->writeCommand(LCD_DISP_OFF);              /* display off                  */
	this->clearScreen();                           /* display clear                */
	this->writeCommand(LCD_MODE_DEFAULT);          /* set entry mode               */
	this->writeCommand(LCD_DISP_ON_CURSOR);        /* display/cursor control       */

}

void LCD::open(uint8_t numLines, uint8_t numColumns)
{
	this->numLines = numLines;
	this->numLines = numColumns;
}

int8_t LCD::writeCommand(uint8_t command)
{
	return this->lcdTransmitter->writeCommand(command);
}

int8_t LCD::writeByte(uint8_t byte)
{
	return this->lcdTransmitter->writeByte(byte, DATA_MODE);
}

int8_t LCD::writeBytes(uint8_t* buffer, uint8_t length)
{
	int8_t retVal;
	
	for (uint8_t index = 0; index < length; ++index)
	{
		retVal = this->writeByte(buffer[index]);
		if (retVal != LCD_OK)
		{
			return LCD_NOK;
		}
	}
}

int8_t LCD::writeString(const char* text)
{
	int8_t retVal;
	uint8_t textLength = strlen(text);
	
	for (uint8_t index = 0; index < textLength; ++index)
	{
		retVal = this->writeByte(text[index]);
	}
}

int8_t LCD::setCursor(uint8_t nX, uint8_t nY)
{
	unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
	return this->writeCommand(firstCharAdr[nY-1] + nX - 1);
	//_delay_us(100);
}

int8_t LCD::display(uint8_t ledOnOff)
{
	return this->lcdTransmitter->display(ledOnOff);
}

int8_t LCD::clearScreen(void)
{
	this->lcdTransmitter->writeCommand(1 << LCD_CLR);
}

int8_t LCD::home(void)
{
	this->lcdTransmitter->writeCommand(1<<LCD_HOME);
}