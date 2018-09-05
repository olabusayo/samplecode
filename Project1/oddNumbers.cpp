#include <stdio.h>
#include <stdlib.h>

int * oddNumbers(int l, int r, int * result_count);

int* oddNumbers(int l, int r, int* result_count) {
	int size = 100000, count = 0;
	int * arr = (int *) calloc(sizeof(int), size);

	if (arr == NULL) {
		printf("ISSUE WITH CALLOC\n");
	}

	for (int i = l; i <= r; i++) {
		if ((i % 2) != 0) {//odd
			arr[count] = i;
			count++;
		}
	}

	*result_count = count;
	return arr;

}


/*int main() {
	int l = 5000, r = 100000;
	int result_count = 0;
	int * arr = NULL;

	printf("Hello World");

	arr = oddNumbers(l, r, &result_count);

	for (int i = 0; i < result_count; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}*/