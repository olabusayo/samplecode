#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"
#include "TimesTable.h"
#include "Computations.h"
#include "DiceRoller.h"

#define INPUT_SIZE 100
#define DATA_SIZE 200
#define DOUBLE_MAX 10000000
#define MAX_VAL_MULT 10000000
#define OPTION_SIZE 10
#define MAX_DICE 50
#define MAX_SIDES 20
#define MAX_ROLLS 50

int main() {

	/*generic vars*/
	char option[OPTION_SIZE] = {0}, input[INPUT_SIZE] = {0}, delim = ' ';
   char *errPtr = NULL;
	long long_input_arr[INPUT_SIZE] = {0};
	int size_array = 0;
   long num = 0;
	long sides = 0, dice = 0, rolls = 0;

	/*computational vars*/
	double radius = 0, area = 0, side = 0, volume = 0;
   int saveResult = 0; 
	char resultsData[DATA_SIZE] = {0}, 
        volumeAbsolutePath[] = "/tmp/volumeOfCubes",
        areaAbsolutePath[] = "/tmp/areaOfCircles";
   
   /*set the seed*/
   srand((unsigned int)time( NULL) );

	//display menu options
	do {
		printf("\nWould you like to: \n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n%s",
			"1) Roll some Dice",
			"2) Calculate Area of Circle",
			"3) Compute Volume of Cube",
			"4) Generate Multiplication Tables", 
			"5) Exit",
	"Selection: ");

		//get option input
      Utils_getLine(option, OPTION_SIZE);
      num = Utils_stringToLong(option, &errPtr);

		//check validity
		switch(num) {
			//dice roller
			case 1:
				printf("You've chosen to roll some dice\n");
            do {
                printf("Input number of dice (max: %d): ", MAX_DICE);
                Utils_getLine(input, INPUT_SIZE);
                dice = Utils_stringToLong(input, &errPtr);
                if( dice <= 0 ) { 
                    printf("Sides, dice or rolls cannot be less than or equal to 0\n");
                }
            } while (dice <= 0 || dice > MAX_DICE);
            do {
                printf("Input number of sides (max: %d): ", MAX_SIDES);
                Utils_getLine(input, INPUT_SIZE);
                sides = Utils_stringToLong(input, &errPtr);
                if( sides <= 0 ) { 
                    printf("Sides, dice or rolls cannot be less than or equal to 0\n");
                }
            } while (sides <= 0 || sides > MAX_SIDES);
            do {
                printf("Input number of rolls (max: %d): ", MAX_ROLLS);
                Utils_getLine(input, INPUT_SIZE);
                rolls = Utils_stringToLong(input, &errPtr);
                if( rolls <= 0 ) {
                    printf("Sides, dice or rolls cannot be less than or equal to 0\n");
                }
            } while (rolls <= 0 || rolls > MAX_ROLLS);
				
				if( sides > 0 && dice > 0 && rolls > 0 ) {
					DiceRoller_rollDice(sides, dice, rolls);
				} else {
					printf("Sides, dice or rolls cannot be less than or equal to 0\n");
				}
				break;
			//area of circle
			case 2:
				printf("You've chosen to compute area of circle\n");
				do {
				    printf("Please input radius of circle (max: %d): ", DOUBLE_MAX);
                Utils_getLine(input, INPUT_SIZE);
				    radius = Utils_stringToDouble(input, &errPtr);
                if( radius <= 0 ) {
                    printf("Radius cannot be less than or equal to 0. Try again.\n");
                }
            } while(radius <= 0 || radius > DOUBLE_MAX);
				
				area = Computations_calculateArea(radius);
            if (area != 0) {
                snprintf(resultsData, DATA_SIZE, "Area of Circle with Radius of %.6f = %.6f", radius, area);
                printf("%s\n", resultsData);
                
                if( Utils_askToSaveResults() ) {
                    //results of save attempt
                    saveResult = Utils_saveToDisk(areaAbsolutePath, resultsData); 
                    if ( saveResult < 0 ) {
                       printf("Save to disk unsuccesful: %s\n", (saveResult == -2 ? "Error Opening File" : "Error Printing to File")) ;
                    }
                }
            } else {
                printf("Issue with calculating area of circle with radius %f\n", radius);
            }
				break;
			//volume of cube
			case 3:
				printf("You've chosen to compute volume of a cube\n");
            do {
				    printf("Please input length, width or height of cube (max: %d): ", DOUBLE_MAX);
				    Utils_getLine(input, INPUT_SIZE);
				    side = Utils_stringToDouble(input, &errPtr);
                if( side <= 0 ) {
                    printf("Side cannot be less than or equal to 0. Try again.\n");
                }
            } while (side <= 0 || side > DOUBLE_MAX);
				
            volume = Computations_calculateVolumeCube(side);
				if(volume != 0 ) {
					snprintf(resultsData, DATA_SIZE, "Volume of %.5f x %.6f x %.6f cube = %.6f", side, side, side, volume);
					printf("%s\n", resultsData);
					
					if( Utils_askToSaveResults() ) {
                   //results of save attempt
                   saveResult = Utils_saveToDisk(volumeAbsolutePath, resultsData); 
                   if ( saveResult < 0 ) {
                      printf("Save to disk unsuccesful: %s\n", (saveResult == -2 ? "Error Opening File" : "Error Printing to File")) ;
                   }
               }
				} else {
					printf("Issue with calculating volume of cube with side of %f\n", side);
				}
				break;
			//times table
			case 4:
				printf("You've chose to generate multiplication (times) tables\n");
            do {
                printf("Please enter numbers (separated by space) for multiplication table generation (max chars: %d | min val: 1 | max value of each num: %d)): ", INPUT_SIZE, MAX_VAL_MULT);
                Utils_getLine(input, INPUT_SIZE);
                
                size_array = Utils_stringToArrayOfLongs(input, delim, long_input_arr, INPUT_SIZE, MAX_VAL_MULT);
                if(size_array > 0) {
                    TimesTable_generateTimesTable(long_input_arr, size_array);
                } else {
                    printf("Input of %s was invalid! Try again\n", input);
                }
            } while(size_array <= 0);
				break;
			case 5:
				printf("You've chosen to exit! Goodbye!\n");
				break;
         default:
            printf("Invalid option entered: %s. Try again!\n", option);
		}
	} while (num != 5);
	return 0;
}
