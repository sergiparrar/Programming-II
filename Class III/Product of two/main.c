#include <stdio.h>

int main(){
	int n1, n2;
	int result = 0;

	printf("Input two numbers to multiply.\n");

	scanf_s("%d%d", &n1, &n2);
	fflush(stdin);

	printf("%d times %d is equal to ", n1, n2);

	while (n2-- > 0){
		result += n1;
	}
	
	printf("%d\n", result);

	getchar();
	return 0;
}