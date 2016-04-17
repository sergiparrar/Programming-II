#include "dynarray.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	darray<int> myarray;

	printf("Original Size: %d\nOriginal Capacity: %d\n", myarray.size(), myarray.capacity());

	myarray.push_back(0);
	myarray.push_back(1);
	myarray.push_back(2);
	myarray.push_back(3);
	myarray.push_back(4);

	myarray.insert(5, 5, 12);

	for (int i = 0; i < myarray.size(); i++)
	{
		printf("%d\n", myarray[i]);
	}

	printf("Size: %d\nCapacity: %d\nEmptying...", myarray.size(), myarray.capacity());

	while (!myarray.empty())
		myarray.pop_back();

	printf("\nSize: %d\nCapacity: %d\n", myarray.size(), myarray.capacity());

	getchar();
	return 0;
}