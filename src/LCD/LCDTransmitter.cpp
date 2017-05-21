/*
 * LCDTransmitter.cpp
 *
 * Created: 5/21/2017 8:26:06 AM
 *  Author: fairenough
 */ 

#include "LCDTransmitter.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif

LCDTransmitter::LCDTransmitter (I2CAdapter* newI2cAdapter) : i2cAdapter (newI2cAdapter){}

int8_t LCDTransmitter::writeByte(uint8_t byte, const uint8_t MODE)
{
	uint8_t sequenceLength = MODE;
	int8_t retVal;
	uint8_t sequenceBytes[sequenceLength];
		
	retVal = this->waitIfBusy();
	if (retVal != LCD_OK)
	{
		return LCD_NOK;
	}
	
	// Send High Nibble
	this->adapterOutputPort = byte & 0xF0;
	sequenceBytes[0] = adapterOutputPort;
	// Sending data   RS = 1, RW = 0
	// Sending command RS = 0 , RW = 0
	if (MODE == LCD_DATA_MODE)
	{
		this->adapterOutputPort |= 1 << LCD_REGISTER_SELECT;
	}
	else if (MODE == COMMAND_MODE)
	{
		this->adapterOutputPort &= ~(1 << LCD_REGISTER_SELECT);
	}
	this->adapterOutputPort &= ~(1 << LCD_READ_WRITE);
	sequenceBytes[1] = adapterOutputPort;
	
	this->setWritePinBytes(sequenceBytes, 2);
		
	// Same Send Low Nibble
	this->adapterOutputPort = byte << 4;
	sequenceBytes[4] = adapterOutputPort;
	
	// Sending data   RS = 1, RW = 0
	if (MODE == DATA_MODE)
	{
		this->adapterOutputPort |= 1 << LCD_REGISTER_SELECT;
		this->adapterOutputPort &= ~(1 << LCD_READ_WRITE);
		sequenceBytes[5] = adapterOutputPort;
	}	
	
	this->setWritePinBytes(sequenceBytes, sequenceLength - 2);

	retVal = this->i2cAdapter->writeBytes(sequenceBytes, sequenceLength);
	if (retVal != I2C_ADAPTER_NOK)
	{
		return LCD_NOK;
	}
	return LCD_OK;	
}

int8_t LCDTransmitter::writeBytes(uint8_t* buffer, uint8_t length)
{
	int8_t retVal;
	
	for (uint8_t index = 0; index < length; ++length)
	{
		retVal = this->writeByte(buffer[index], DATA_MODE);
		if (retVal != LCD_OK)
		{
			return LCD_NOK;
		}
	}
	return LCD_OK;
}

int8_t LCDTransmitter::writeCommand(uint8_t command)
{
	return this->writeByte(command, COMMAND_MODE);
}

int8_t LCDTransmitter::waitIfBusy()
{
	 uint8_t adapterPort;
	 int8_t retVal;
	 
	 /* wait until busy flag is cleared */
	 do 
	 {
		 adapterPort = this->i2cAdapter->readByte(&adapterPort);
		 if (retVal != LCD_OK)
		 {
			 return LCD_NOK;
		 }
	 } 
	 while ( adapterPort & (1<<LCD_BUSY) );
	 
	 return LCD_OK;  
}

void LCDTransmitter::setWritePinBytes(uint8_t* sequenceBytes, uint8_t startIndex)
{	
	// Send L - > H
	this->adapterOutputPort |= (1 << LCD_ENABLE);
	sequenceBytes[startIndex] = adapterOutputPort;
	// Send H - > L
	this->adapterOutputPort &= ~(1 << LCD_ENABLE);
	sequenceBytes[startIndex + 1] = adapterOutputPort;
}

int8_t LCDTransmitter::display(uint8_t ledOnOff)
{
	if (LCD_DISP_ON == ledOnOff)
	{
		this->adapterOutputPort &= ~(1 << LCD_LED_PIN);		
	}
	
	else if (LCD_DISP_OFF == ledOnOff)
	{
		this->adapterOutputPort |= (1 << LCD_LED_PIN);
	}
	
	return this->i2cAdapter->writeBytes(&adapterOutputPort, 1);	
}

///* toggle Enable Pin to initiate write */
//void LCDTransmitter::setToggleEnablePinBytes(uint8_t* sequenceBytes, uint8_t startIndex)
//{
	//// Low - > High Pulse
	//adapterOutputPort |= (1 << ENABLE);
	//sequenceBytes[startIndex - 2] = adapterOutputPort;
	//// Same H - > L
	//adapterOutputPort &= ~(1 << ENABLE);
	//sequenceBytes[startIndex - 1] = adapterOutputPort;
//}