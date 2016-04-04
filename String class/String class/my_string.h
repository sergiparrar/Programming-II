#ifndef __MY_STRING_H__
#define __MY_STRING_H__
#include <string.h>

class mstring
{
private:
	char* local_str;
	void alloc(unsigned int size)
	{
		local_str = new char[size];
	}

public:
	mstring()
	{
		alloc(1);
		local_str = '\0';
	}

	mstring(const char* new_str)
	{
		int size = strlen(new_str) + 1;
		alloc(size);
		strcpy_s(local_str, size, new_str);
	}

	~mstring()
	{
		delete[] local_str;
		local_str = nullptr;
	}

	unsigned int length() const
	{
		return strlen(local_str);
	}

	char* c_str() const
	{
		return local_str;
	}

	bool operator == (const mstring cstr)
	{
		return strcmp(local_str, cstr.c_str());
	}
	

};

#endif //__MY_STRING_H__