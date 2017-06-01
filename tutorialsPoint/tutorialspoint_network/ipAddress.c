#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main() {

    int retval;
    struct in_addr addr;
    
    char *str="127.0.0.1";

    memset(&addr, '\0', sizeof(addr));

    retval = inet_aton(str, &addr);

    printf("retval: %d\n", retval);

    if(retval == 1) {
        printf("inet_aton: %ld\n", addr.s_addr);
    }

    printf("inet_addr: %ld\n", inet_addr(str));

    printf("inet_ntoa: %s\n", inet_ntoa(addr));
    return 0;
}
