#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int minPower(int p_count, int* p);

int minPower(int p_count, int* p) {
	int score = 0, min_needed = 0, abs_needed = 0;

	for (int i = 0; i < p_count; i++) {
		score += p[i];
		if (score < 1) {
			abs_needed = abs((score - 1));
			min_needed += abs_needed;
			score += abs_needed;
		}
	}

	return min_needed;
}

/*
int main() {

	int arr[] = { -5,4,-2,3,1,-1,-6,-1,0,5 };
	int min_score = 0;

	min_score = minPower(sizeof(arr)/sizeof(int), arr);
	return 0;
}*/