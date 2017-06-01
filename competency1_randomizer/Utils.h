#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

void Utils_flushStream(FILE *stream);
long Utils_stringToLong(const char * str, char **errPtr);
double Utils_stringToDouble(const char * str, char **errPtr);
long Utils_stringToArrayOfLongs (const char * str, char tokenDelim, long arr[], int size, int max_val );
void Utils_getLine(char * str, int size);
int Utils_saveToDisk(const char * path, const char * data);
int Utils_askToSaveResults();
void validateFilePath(char * path, int maxSize);

#endif /*UTILS_H*/
