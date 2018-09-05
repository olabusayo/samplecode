#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

char* findNumber(int arr_count, int* arr, int k);

char* findNumber(int arr_count, int* arr, int k) {

	char * resp = (char *)calloc(sizeof(char), 5);
	for (int i = 0; i < arr_count; i++) {
		if (k == arr[i]) {
			strncpy(resp, "YES", 3);
			break;
		}
	}

	if (strlen(resp) == 0) {
		strncpy(resp, "NO", 2);
	}

	return resp;

}

int main() {

	char * resp = NULL;
	int arr[] = { 1,3,7,9,11,14,17,18,19,22 };

	resp = findNumber(10, arr, 13);

	printf("%s", resp);


	return 0;
}
