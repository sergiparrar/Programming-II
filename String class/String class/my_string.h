#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <string.h>
#include <stdlib.h>
#define MYSTRING_BLOCK_SIZE 15
#define mstring MyString

class MyString
{
private:
	char* _str;
	unsigned int _capacity;
	unsigned int _size;

	void _alloc(const unsigned int& size)
	{
		_str = (char*) realloc(_str, (size + 1) * sizeof(char));
	}

public:
	static const unsigned int npos = -1;

public:
	MyString():
		_capacity(MYSTRING_BLOCK_SIZE),
		_size(0)
	{
		_alloc(_capacity);
		*_str = '\0';
	}

	MyString(const char* reference)
	{
		_size = strlen(reference);
		_capacity = MYSTRING_BLOCK_SIZE * (_size / MYSTRING_BLOCK_SIZE + 1);

		_alloc(_capacity);
		char* str = _str;
		for (int i = 0; i < _size; ++i)
		{
			*str = *reference;
			++str;
			++reference;
		}
		*str = '\0';
	}

	MyString(const MyString& reference)
	{
		_size = reference.size();
		_capacity = reference.capacity();

		_alloc(_capacity);
		char* str = _str;
		for (int i = 0; i < _size; ++i)
		{
			*str = reference[i];
			++str;
		}
		*str = '\0';
	}

	~MyString()
	{
		free(_str);
		_str = nullptr;
	}


	unsigned int size() const
	{
		return _size;
	}

	unsigned int capacity() const
	{
		return _capacity;
	}

	char* c_str() const
	{
		return _str;
	}


	void operator= (const MyString& reference)
	{
		_size = reference.size();
		_capacity = reference.capacity();

		_alloc(_capacity);
		char* str = _str;
		for (int i = 0; i < _size; ++i)
		{
			*str = reference[i];
			++str;
		}
		*str = '\0';
	}

	void operator= (const char* reference)
	{
		_size = strlen(reference);
		_capacity = MYSTRING_BLOCK_SIZE * (_size / MYSTRING_BLOCK_SIZE + 1);

		_alloc(_capacity);
		char* str = _str;
		for (int i = 0; i < _size; ++i)
		{
			*str = *reference;
			++str;
			++reference;
		}
		*str = '\0';
	}

	void operator+= (const MyString& apend)
	{
		char* str = _str + _size;
		_size += apend.size();
		_capacity += apend.capacity();

		_alloc(_capacity);
		for (int i = 0; i < apend.size(); ++i)
		{
			*str = apend[i];
			++str;
		}
		*str = '\0';
	}

	void operator+= (const char* apend)
	{
		char* str = _str + _size;
		unsigned int apend_size = strlen(apend);
		_size += apend_size;
		_capacity += MYSTRING_BLOCK_SIZE * (_size / MYSTRING_BLOCK_SIZE + 1);

		_alloc(_capacity);
		for (int i = 0; i < apend_size; ++i)
		{
			*str = *apend;
			++str;
			++apend;
		}
		*str = '\0';
	}

	char& operator[] (const unsigned int& pos) const
	{
		char* str = _str + pos * sizeof(char);
		return *str;
	}

	char& operator[] (const unsigned int& pos)
	{
		char* str = _str + pos * sizeof(char);
		return *str;
	}

	bool operator== (const MyString& rstr)
	{
		return strcmp(_str, rstr.c_str()) == 0;
	}

	bool operator== (const char* rstr)
	{
		return strcmp(_str, rstr) == 0;
	}

	bool operator!= (const MyString& rstr)
	{
		return strcmp(_str, rstr.c_str()) != 0;
	}

	bool operator!= (const char* rstr)
	{
		return strcmp(_str, rstr) != 0;
	}

	void push_back(const char& c)
	{
		if (_size >= _capacity)
		{
			_capacity += MYSTRING_BLOCK_SIZE;
			_alloc(_capacity);
		}

		char* str = _str + _size++;
		*str = c;
		str++;
		*str = '\0';
	}

	MyString substr(const unsigned int& pos, const unsigned int& length = 1)
	{
		MyString substr;
		char* str = _str + pos;

		for (int i = 0; i < length; i++)
		{
			substr.push_back(*str);
			str++;
		}

		return substr;
	}
	
	unsigned int find(const char* substr, const unsigned int& pos = 0) const
	{
		char* str = _str + pos;
		unsigned int subsize = strlen(substr);
		unsigned int res = pos;
		while (strncmp(str, substr, subsize) != 0 && res <= (_size - subsize) )
		{
			++res;
			++str;
		}

		if (res > _size - subsize)
			res = npos;

		return res;
	}

	unsigned int find(const MyString& substr, const unsigned int& pos = 0) const
	{
		char* str = _str + pos;
		unsigned int res = pos;
		while (strncmp(str, substr.c_str(), substr.size()) != 0 && res <= (_size - substr.size()))
		{
			++res;
			++str;
		}

		if (res > _size - substr.size())
			return npos;

		return res;
	}

};

#endif //__MY_STRING_H__