#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

char* winner(int andrea_count, int* andrea, int maria_count, int* maria, char* s);

char* winner(int andrea_count, int* andrea, int maria_count, int* maria, char* s) {
	int aScore = 0, mScore = 0;
	int odd = 0, even = 0;
	char * resp = (char *)calloc(10, sizeof(char));

	if ( strncmp(s, "ODD", 3) == 0 ) {
		odd = 1;
	}
	else {
		even = 1;
	}

	for ( int i = 0; i < andrea_count; i++) {
		if ((i % 2) != 0) {//index is odd
			if (!odd) {
				continue; //skip
			}
		}
		else {//index is even
			if (!even) {
				continue; 
			}
		}
	
		aScore += (andrea[i] - maria[i]);
		mScore += (maria[i] - andrea[i]);
		printf("Andrea: %d Maria: %d\n", aScore, mScore);

	}

	if (aScore > mScore) {
		strncpy(resp, "Andrea", strlen("Andrea"));
	}
	else if (aScore < mScore) {
		strncpy(resp, "Maria", strlen("Maria"));
	}
	else {
		strncpy(resp, "Tie", strlen("Tie"));
	}

	return resp;
}

int main() {
	char * resp = NULL;
	int andrea[] = {3,5,6,7};
	int maria[] = {4,5,7,2};
	resp = winner(sizeof(andrea)/sizeof(int), andrea, sizeof(maria)/sizeof(int), maria, (char *) "ODD");
	printf("%s is Winner!\n", resp);
	return 0;
}