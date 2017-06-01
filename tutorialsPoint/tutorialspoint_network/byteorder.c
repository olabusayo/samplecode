#include <stdio.h>

int main() {

    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;

    if(sizeof(short) == 2) {
        if( un.c[0] == 1 && un.c[1] == 2) {
            printf("Big Endian Byte Order\n");
        } else if (un.c[0] == 2 && un.c[1] == 1) {
            printf("Little Endian Byte Order\n");
        } else {
            printf("Unknown\n");
        }
    } else {
        printf("sizeof(short) = %d\n", sizeof(short));
    }

    return 0;
}
