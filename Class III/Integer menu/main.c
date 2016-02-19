#include <stdio.h>
#include "functions.h"

int main(){
	printf("Please introduce an integer to work with.\n");
	int integer;
	scanf_s("%d", &integer);
	fflush(stdin);

	char command;
	print_menu(&integer);
	while (scanf_s("%c", &command, 1) && command != 'd'){
		fflush(stdin);

		switch (command){
		case 'a': ++integer; break;
		case 'b': --integer; break;
		case 'c': integer *= integer; break;
		default: printf("That is not a valid command!\n");
		}

		print_menu(&integer);
	}

	getchar();
	return 0;
}