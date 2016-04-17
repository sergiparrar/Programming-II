#include "my_string.h"
#include <stdio.h>
#include <iostream> 
using namespace std;

int main(){
	mstring dummy = "Hello";
	printf("%s\n", dummy.c_str());
	if (dummy == "Hello") cout << "Correct!" << endl;
	else cout << "Nope" << endl;
	dummy += " SO NICE";
	printf("%s\n", dummy.c_str());
	if (dummy == "Hello SO NICE") cout << "Correct!" << endl;
	else cout << "Nope" << endl;
	mstring dummy2 = dummy.substr(6, 7);
	printf("%s\n", dummy2.c_str());
	if (dummy2 == "SO NICE") cout << "Correct!" << endl;
	else cout << "Nope" << endl;
	printf("%d\n", dummy.find(dummy2));
	getchar();
	return 0;
}