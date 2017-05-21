/*
 * I2CAdapter.cpp
 *
 * Created: 5/20/2017 8:07:23 PM
 *  Author: fairenough
 */ 
#ifndef _I2C_ADAPTER_H_
#define _I2C_ADAPTER_H_

#include "I2CPort.h"

#define I2C_ADAPTER_OK  0
#define I2C_ADAPTER_NOK -1
#define DEFAULT_ADDRESS 0x3F

class I2CAdapter
{
	private:
		I2CPort* i2cPort;
		uint8_t address;
		
	public:
	    I2CAdapter(I2CPort* i2cPort);
		void setAddress(uint8_t address);
		int8_t writeBytes(uint8_t* buffer, uint8_t length);
		int8_t readByte(uint8_t* data);	
};

#endif

