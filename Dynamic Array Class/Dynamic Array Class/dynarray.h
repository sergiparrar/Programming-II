#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#include <stdlib.h>
#define DYNARRAY_BLOCK_SIZE 16

template <class T> class DynArray
{
private:
	T* buffer;
	unsigned int capacity;
	unsigned int size;

public:
	DynArray::DynArray():
		capacity (DYNARRAY_BLOCK_SIZE),
		size(0)
	{
		buffer = (T*)malloc(sizeof(T) * capacity);
	}

	DynArray::DynArray(const unsigned int _size, const T _value = NULL)
	{
		capacity = DYNARRAY_BLOCK_SIZE * (_size / DYNARRAY_BLOCK_SIZE + 1);
		buffer = (T*)malloc(sizeof(T)* capacity);

		size = _size;
		for (int i = 0; i < size; ++i)
			buffer* = _value;
	}

	DynArray::DynArray(const DynArray<T>& reference)
	{
		capacity = reference.capacity;
		buffer = (T*)malloc(sizeof(T)* capacity);

		size = reference.size;
		for (int i = 0; i < size; ++i)
		{
			T* _buffer = buffer;
			_buffer++ = reference.buffer++;
		}
	}

	DynArray::~DynArray()
	{
		free(buffer);
		buffer = nullptr;
	}

};




#endif