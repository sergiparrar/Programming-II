#include <stdio.h>

int main(){
	printf("Please introduce 10 integers.\n");

	int result;
	scanf_s("%d", &result);
	fflush(stdin);

	for (int i = 0; i < 9; ++i){
		int current_number;
		scanf_s("%d", &current_number);
		fflush(stdin);

		if (current_number < result) result = current_number;
	}

	printf("The smallest number was %d.", result);

	getchar();
	return 0;
}