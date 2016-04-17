#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#include <stdlib.h>
#define DYNARRAY_BLOCK_SIZE 16
#define darray DynArray

template <class T> class DynArray
{
private:
	T* _buffer;
	unsigned int _capacity;
	unsigned int _size;

public:
	DynArray():
		_capacity(DYNARRAY_BLOCK_SIZE),
		_size(0)
	{
		_buffer = (T*)malloc(sizeof(T) * _capacity);
	}

	DynArray(const unsigned int& size, const T& value = 0)
	{
		_capacity = DYNARRAY_BLOCK_SIZE * (size / DYNARRAY_BLOCK_SIZE + 1);
		_buffer = (T*)malloc(sizeof(T) * _capacity);
		_size = size;

		T* buffer = _buffer;
		for (int i = 0; i < _size; ++i)
			*buffer = value;
	} //this constructor and the default one could be merged with DynArray(const unsigned int& size = 0, const T& value = 0)

	DynArray(const DynArray<T>& reference)
	{
		_capacity = reference.capacity();
		_buffer = (T*)malloc(sizeof(T)* _capacity);
		_size = reference.size();

		T* buffer = _buffer;
		for (int i = 0; i < _size; ++i)
		{
			*buffer = reference[i];
			buffer++;
		}
	}

	~DynArray()
	{
		free(_buffer);
		_buffer = nullptr;
	}

	T& operator[] (const unsigned int& pos) const
	{
		T* buffer = _buffer + pos;

		return *buffer;
	}

	T& operator[] (const unsigned int& pos)
	{
		T* buffer = _buffer;
		buffer += pos;

		return *buffer;
	}

	unsigned int size() const
	{
		return _size;
	}

	unsigned int capacity() const
	{
		return _capacity;
	}

	bool empty()
	{
		return _size == 0;
	}

	void push_back(const T& item)
	{
		if (_size >= _capacity)
		{
			_buffer = (T*)realloc(_buffer, (_capacity + DYNARRAY_BLOCK_SIZE)*sizeof(T));
			_capacity += DYNARRAY_BLOCK_SIZE;
		}

		T* buffer = _buffer + _size++;
		*buffer = item;
	}

	void pop_back()
	{
		--_size;
	}

	void insert(const unsigned int& position, const T& value, const unsigned int& nelements = 1)
	{
		_size += nelements;
		if (_size > _capacity)
		{
			_buffer = (T*)realloc(_buffer, (_capacity + DYNARRAY_BLOCK_SIZE)*sizeof(T));
			_capacity += DYNARRAY_BLOCK_SIZE;
		}

		T* buffer = _buffer + _size - nelements;
		T* buffer_end = _buffer + _size;

		for (int i = 0; i <= nelements; ++i)
		{
			*buffer_end = *buffer;
			++buffer;
			++buffer_end;
		}

		for (int i = 0; i <= nelements; ++i)
		{
			--buffer;
			*buffer = value;
		}
		
	}

	void remove(const unsigned int& first, unsigned int last = 0)
	{
		if (last < first)
			last = first;
		T* buffer = _buffer + first;
		T* buffer_end = _buffer + last + 1;

		for (int i = 0; i < (_size -1) - last; ++i)
		{
			*buffer = *buffer_end;
			++buffer;
			++buffer_end;
		}

		_size -= last - first + 1;
	}

};

#endif //__DYNARRAY_H__