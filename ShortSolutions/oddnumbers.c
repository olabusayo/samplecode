#include <stdio.h>

int* oddNumbers(int l, int r, int* result_count) {
	int size = 10 ^ 5, count = 0;
	int * arr = calloc(sizeof(int), size);
	if (arr == NULL) {
		printf("ISSUE WITH CALLOC\n");
	}

	for (int i = l; i <= r; i++) {
		if ((i % 2) != 0) {//odd
			arr[count] = i;
			count++;
		}
	}
	printf("%d\n", count);
	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}

	*result_count = count;
	return arr;

}

int main() {
	int l = 1, r = 5;
	int result_count = 0;
	int * arr = NULL;

	arr = oddNumbers(l, r, &result_count);

	for (int i = 0; i < result_count; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}