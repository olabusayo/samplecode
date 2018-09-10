#include <stdio.h>
#include <stdlib.h>

int consecutive(long num);

int consecutive(long num) {
	
	/*
	long sum = 0;
	int record = 0;
	for (long i = 1; i < num; i++) {

		for (long j = i; j < num; j++) {
			sum += j;
			if (sum == num) {
				printf("I got %d with nums %d to %d\n", num, i, j);
				record++;
				break;
			}
			else if (sum > num) {
				printf("No luck from %d to %d, got %d\n", i, j, sum);
				break;
			}
		}
		sum = 0;
	}
	*/

	///*	
	long sum = 0;
	int record = 0;
	long max = (num/2) + 2;
	for (long i = 1; i < max; i++) {

		for (long j = i; j < max; j++) {
			sum += j;
			if (sum == num) {
				printf("I got %d with nums %d to %d\n", num, i, j);
				record++;
				break;
			}
			else if (sum > num) {
				printf("No luck from %d to %d, got %d\n", i, j, sum);
				break;
			}
		}
		sum = 0;
	}

	//*/
	return record;
}

/*int main() {

	int num = 0;

	num = consecutive(15);

	return 0;
}*/
