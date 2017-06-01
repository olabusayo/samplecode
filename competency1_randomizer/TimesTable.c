#include "TimesTable.h"

void TimesTable_generateTimesTable(long * nums, int size_array) {
	int i, k, maxMultiple = 12;
	for (i = 1; i <= maxMultiple; i++) {
		printf("\n");
		for (k = 0; k < size_array; k++) {
			printf("%ld x %d = %ld\t", nums[k], i, (nums[k] < LONG_MAX/maxMultiple ? (nums[k]*i): 0));
		}
	}
	printf("\n");
}
