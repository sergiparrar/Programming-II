#include <stdlib.h>
using namespace std;

int main()
{
	int* marray = new int[5];
	marray = (int*) realloc(marray, sizeof(marray) + sizeof(int) * 2);
	for (int i = 0; i < 7;i++)
		*marray++ = 1;
	delete[] marray;
}