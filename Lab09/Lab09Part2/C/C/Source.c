#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	printf("Russell Harvey\n");
	printf("Enter an integer: ");
	char input1[10];
	scanf_s("%s", input1, 10);
	int numb1;
	numb1 = atoi(input1);
	printf("Enter another integer: ");
	char input2[10];
	scanf_s("%s", input2, 10);
	int numb2;
	numb2 = atoi(input2);
	int result = (numb1 * numb1) + (numb2 * numb2);
	printf("The sum of squares is: %d\n", result);
	int a, b, c, d;
	a = (numb1 >> 24) & 0xff;
	b = (numb1 >> 16) & 0xff;  
	c = (numb1 >> 8) & 0xff; 
	d = numb1 & 0xff;
	int result2 = a + b + c + d;
	printf("The sum of bytes is: %d\n", result2);
}