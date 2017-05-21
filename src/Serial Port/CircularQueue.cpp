#include "CircularQueue.h"

CircularQueue::CircularQueue()
{
	this->head = 0;
	this->tail = 0;
	this->availableItems = 0;

	for (unsigned char i = 0; i < BUFFER_SIZE; ++i)
	{
		this->buffer[i] = 0;
	}
}

/**
 * @brief Returns if data available in the Circular Queue
 *
 * @param none
 *
 * @return true if data any data is available for read
 */
bool CircularQueue::isAvailable()
{
	if (this->availableItems)
	{
		return true;
	}
	return false;
}

uint8_t CircularQueue::getAvailableItems()
{
	return this->availableItems;
}

bool CircularQueue::isEmpty()
{
	if (this->availableItems)
	{
		return false;
	}
	return true;
}

bool CircularQueue::isFull()
{
	if (this->availableItems == BUFFER_SIZE)
	{
		return true;
	}
	return false;
}

bool CircularQueue::enqueue(unsigned char element)
{
	if (this->isFull())
	{
		return false;
	}
	
	this->tail = (this->tail + 1) & BUFFER_MASK;
	this->buffer[this->tail] = element;
	this->availableItems++;
	
	return true;
}

bool CircularQueue::dequeue(unsigned char* byte)
{
	if (this->isEmpty())
	{
		return false;
	}
	
	this->head = (this->head + 1) & BUFFER_MASK;
	*byte = this->buffer[this->head];
	this->availableItems--;
	
	return true;
}

