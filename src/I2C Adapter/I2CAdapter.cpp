/*
 * I2CAdapter.cpp
 *
 * Created: 5/20/2017 8:25:59 PM
 *  Author: fairenough
 */ 
#include "I2CAdapter.h"
#include <util/delay.h>

I2CAdapter::I2CAdapter(I2CPort* i2cPort)
{
	this->i2cPort = i2cPort;
	this->i2cPort->selectSlaveDevice(DEFAULT_ADDRESS);
	this->address = DEFAULT_ADDRESS;
}

void I2CAdapter::setAddress(uint8_t address)
{
	this->address = address;
}

int8_t I2CAdapter::writeBytes(uint8_t* buffer, uint8_t length)
{
	int8_t retVal;
	
	this->i2cPort->selectSlaveDevice(this->address);
	retVal = i2cPort->writeBytes(buffer, length);
	if (retVal != I2C_OK)
	{
		return I2C_ADAPTER_NOK;
	}
	return I2C_ADAPTER_OK;
}

int8_t I2CAdapter::readByte(uint8_t* data)
{
	int8_t retVal;
	
	this->i2cPort->selectSlaveDevice(this->address);
	retVal = this->i2cPort->readBytes(data, 1);
	if (retVal != I2C_OK)
	{
		return I2C_ADAPTER_NOK;
	}
	return I2C_ADAPTER_OK;
}
