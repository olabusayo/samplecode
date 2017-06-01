#include <stdio.h>

int main() {
    int num = 0, myVar = 10, fac = 1;

    for(num = 1 ; num <= myVar; num++ ) {
        if( num == 1 ) {
            fac *= 1;
            printf("%d! (%d) = 1\n", num, fac);
        } else {
            fac *= num;
            printf("%d! (%d) = %d * %d!\n", num, fac, num, num - 1);
        }
    }

    return 0;
}
