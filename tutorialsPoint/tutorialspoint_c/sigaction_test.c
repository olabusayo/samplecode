#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


struct sigaction oldAct = {0}, newAct = {0};
void handleSignal (int signum);

int main() {

    newAct.sa_handler = handleSignal;
    sigaction(SIGINT, &newAct, NULL);
    int n = 0;
    while( 1 ) {
        printf("%d\t", n++);
        sleep(0);
    }

    
    return 0;
}

void handleSignal (int signum) {
    psignal(signum, "\nsignal name");
    exit(0);
}
