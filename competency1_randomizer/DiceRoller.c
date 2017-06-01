#include "DiceRoller.h"

void DiceRoller_rollDice(long sides, long dice, long rolls) {
	int i;
	printf("For %ld dice, with %ld sides each and %ld rolls: \n", dice, sides, rolls); 	
	for (i = 1; i <= rolls ; i++ ) {
		generateRandomSequence(dice, sides);
	} 
}

void generateRandomSequence(long dice, long sides) {
    int i, j;
	
    for (i = 1; i <= dice; i++) {
    	j = (rand() % sides) + 1;
      printf("%d ",j); 
    }
   printf("\n");
}
