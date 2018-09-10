#include <stdio.h>
#include <stdlib.h>

long climbTheHill(int slope_count, int* slope);

long climbTheHill(int slope_count, int* slope) {
	int inc = 0, dec = 0;
	int notableInc[100] = { 0 }, notableDec[100] = {0};

	for (int i = 1; i < slope_count; i++) {
		
		if (slope[(i - 1)] < slope[i]) {
			inc++;
		}
		else {
			dec++;
		}


	}

	return 0;

}

/*
int main() {

	int arr[] = { -5,4,-2,3,1,-1,-6,-1,0,5 };
	int min_score = 0;

	min_score = climbTheHill(sizeof(arr) / sizeof(int), arr);
	return 0;
}*/