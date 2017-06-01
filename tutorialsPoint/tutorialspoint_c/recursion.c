#include <stdio.h>

int factorial(unsigned int i) {
	int ret;
	if(i <= 1) {
		return 1;
	}
	ret = i * factorial(i - 1);
	printf("~~%d * factorial(%d - 1) = %d\n", i, i, ret);
	return ret;
}

int fibonacci (int i) {
	int ret;
	if ( i == 0 ) { return 0; }
	if ( i == 1 ) { return 1; }
	ret = fibonacci( i - 1) + fibonacci (i -2);
	/*printf("fibonacci(%d - 1) + fibonacci (%d -2) = %d \n", i, i, ret);*/
	return ret;
}

int main() {
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\t", fibonacci(i));
	}
	/*while( 1 ) {
		scanf("%d", &i);
		if ( i > 15 ) {
			printf("Not computing for values above 15\n");
			break;
		}
	printf("Factorial of %d is %d\n", i, factorial(i));
	}*/
	return 0;
}
