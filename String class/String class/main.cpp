#include "my_string.h"
#include <stdio.h>
#include <iostream> 
using namespace std;

int main(){
	mstring dummy = "Hello";
	cout << dummy.c_str() << endl;;
	if (dummy == "Hello") cout << "Correct!" << endl;
	else cout << "Nope" << endl;
	getchar();
}