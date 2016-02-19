#include <stdio.h>
#include "functions.h"

void print_menu(int *integer){
	printf("\nYour integer is %d. What do you want to do?\n", *integer);
	printf("a. Increment integer.\n");
	printf("b. Decrement integer.\n");
	printf("c. Power of two.\n");
	printf("d. Quit.\n");
}
