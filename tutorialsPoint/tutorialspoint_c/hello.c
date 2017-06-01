#include <stdio.h>
#include <limits.h>
#include <float.h>

void func(char*);

static int count = 5;
int main() {

	int var1, i;
	int *ptr, **pptr;
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	int *arrp = arr;
	var1  = 10;
	char str[100];

	char *var2[] = {"string1", "string2", "string3", "string4"};
	/*random comment; do ignore*/
	printf("Hello, world! \n");
	printf("Add var1, %x\n Add var2, %x\n", &var1, &var2);
	/*printf("Size of int: %d\n", sizeof(int));	
	printf("Size of float: %d\n", sizeof(float));	
	printf("Min float: %E\nMax Float: %E\nPrecision Value: %d\n", FLT_MIN,FLT_MAX,FLT_DIG);*/
 
	/*for (i = 0; i < 10; i++) {
		printf("Add arr[%d] = %d\n", i, arr[i]);
		printf("Add arr[%d] = %d\n", i, *(arrp+i));
  	}
	printf("var = %d\nptr addr = %x, ptr val = %d\npptr addr = %x, pptr val = %x, pptr total deref = %d\n", var1, ptr, *ptr, pptr, *pptr, **pptr);	
	ptr = &var1;
	pptr = &ptr;*/

	printf("Gimme me some string :");
	scanf( "%s %d", str, &i );

	printf("Take what you gave :");
	printf( "%s %d", str, i );

                             	
	return 0;
}
