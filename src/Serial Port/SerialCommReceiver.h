#ifndef  _SERIALCOMMRECEIVER_H_
#define	 _SERIALCOMMRECEIVER_H_

#include <stdlib.h>
#include "Readable.h"
#include "CircularQueue.h"
//#include "FreeRTOS.h"
//#include "semphr.h"

#define SERIAL_OK   0
#define SERIAL_NOK -1

class SerialCommReceiver : public Readable
{
	private:
		CircularQueue rxQueue;
		//SemaphoreHandle_t rxBinarySemaphore;

	public:
		SerialCommReceiver();
		int8_t readBytes(uint8_t* buffer, uint8_t length);
		uint8_t available();
		friend class SerialPort;
	private:
		inline int8_t readByte(uint8_t* byte);
};

#endif
