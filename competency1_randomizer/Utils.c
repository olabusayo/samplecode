#include "Utils.h"


//Checks for valid long using strtol
long Utils_stringToLong(const char * str, char **errPtr) {
    long num = 0;

    num = strtol(str, errPtr, 0);
    if(errPtr != NULL && *errPtr != NULL && **errPtr != '\0' ) {
        printf("Issue with input starting at '%c'. Discarding '%s'. Using %ld\n", errPtr[0][0], errPtr[0], num);
    }
    
    return num;
}

/*@brief takes a string and attempts to convert it to a double
 *@param str A c style string
 *@return A double from the string representation of str; if not a valid number, returns 0
 * */
double Utils_stringToDouble(const char * str, char **errPtr) {
    double num = 0;

    num = strtod(str, errPtr);
    if(errPtr != NULL && *errPtr != NULL && **errPtr != '\0' ) {
        printf("Issue with input starting at '%c'. Discarding '%s'. Using %f\n", errPtr[0][0], errPtr[0], num);
    }
    
    return num;
}

/*double Utils_stringToDouble(char * str, char *errPtr) {
    double num;

    num = strtod(str, &errPtr);
    if(errPtr != NULL  && *errPtr != '\0') {
        printf("Issue with input starting at '%c'. Discarding '%s'. Using %f\n", errPtr[0], errPtr, num);
    }
    return num;
}*/

void Utils_flushStream(FILE *stream) {
    char c;
    //printf("Flushing input! '");
    while( (c = getc(stream)) != '\n' && c != EOF ) {
       // printf("%c", c);
    }
    //printf("' Goodbye\n");
}

/*@brief turns string into long array, discarding non valid numbers
 *@param str C String representing input that requires processing into array
 *@param tokenDelim A char representing the delimiter to be used to process input string 
 *@param arr Output parameter, an empty long array that'll hold the non discarded integers from the string str
 *return An long representing the size of the array generated from the string (excluding discarded numbers).
 * */
long Utils_stringToArrayOfLongs (const char * str, char tokenDelim, long arr[], int size, int max_val ) {
   int i = 0;
   if(strlen(str) > 0 ) {
       long num = 0;
       char *token = NULL, *errPtr = NULL;
       char copy[strlen(str)+1];
       strncpy(copy, str, strlen(str)+1);

       token = strtok(copy, &tokenDelim);
       //printf("Token: %s\n", token);
       while(token != NULL && i < size) {
          if(((num = Utils_stringToLong(token, &errPtr)) && num > 0 && num < max_val)) {
             arr[i] = num;
             //printf("arr[i] = %ld\t token:'%s'\n", arr[i], token);
             i++;
          } else {
             printf("Input '%s' discarded; Either non numerical, too large or less than or equal to 0\n", token);
          }
          token = strtok(NULL, &tokenDelim);
       }
   }

   return i;	
}

/*@brief Checks if input path exists or if we have access
 *@param path C String representing directory path
 *@return void
 * */
void validateFilePath(char * path, int maxSize) {
	if( (strlen(path)) <= 0 || strncmp(path,"0", 1) == 0 || strcmp(path, "") == 0 || access( path, F_OK) < 0 ) {
		printf("You selected 0 or cannot access %s. Setting filepath to /tmp\n", path);
		strncpy(path, "/tmp/", maxSize);
	} else if ( path[strlen(path)-1] != '/' ) {
       strncat(path, "/", maxSize-1 );
   }
}

/*@brief Reads and input line from user and turns into C string
 *@param str C string output parameter that captures the user input. Newline in input is replaced with terminating 0
 *@param size integer representing number of characters (-1) to be read in
 *@return no returns
 * */
void Utils_getLine(char * str, int size) {
	char * fgetsStatus;
	fgetsStatus = fgets(str, size, stdin);
	//printf("%s\n", str);
	if( strlen(str) > 0 && str[strlen(str) - 1] != '\n') {
		Utils_flushStream(stdin);
	} else if( fgetsStatus != 0 && str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
		//printf("%s\n", str);
	}
}

int Utils_saveToDisk(const char * path, const char * data) {
	FILE *fp;
	fp = fopen(path, "a");
	int ret;
	if(fp == NULL) {
		perror("Error Opening File: %s");
      printf("Error Opening File: %s\n", path);
		return -2;
	} else {
		printf("Printing data to %s\n", path);
		ret = fprintf( fp, "%s\n", data);
		fclose(fp);
		return ret;
	}
}

int Utils_askToSaveResults() {
   char in;
   int save = -1;

   do {
       printf("Please enter Y to save result to disk or N to not: \n");
       in = fgetc(stdin);
       if( in != '\n') {
           Utils_flushStream(stdin);
       } 
       if( toupper(in) == 'Y' ) {
           save = 1;
       } else if( toupper(in) == 'N' ) {
          save =  0; 
       }
    } while( save != 1 && save != 0 );
   
   return save;
}
