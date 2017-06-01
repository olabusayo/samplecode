#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>

int main() {

    int serverSockFd = 0, clientSockFd = 0, portNo = 6002, cAddrLen = 0;
    struct sockaddr_in localAddr, clientAddr;
    char dataBuffer[256];

    memset(&localAddr, '\0', sizeof(struct sockaddr_in));
    memset(&clientAddr, '\0', sizeof(struct sockaddr_in));
    cAddrLen = sizeof(clientAddr);
    memset(dataBuffer, '\0', sizeof(dataBuffer));

    /* open new TCP server socket */
    serverSockFd = socket(AF_INET, SOCK_STREAM, 6);

    if( serverSockFd < 0 ) {
        perror("Error opening socket!");
        exit(1);
    }

    /*set up localAddr for binding*/
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(portNo);
    localAddr.sin_addr.s_addr = INADDR_ANY;

    /* bind socket to local address on machine */
    if( bind( serverSockFd, (struct sockaddr *) &localAddr, sizeof(struct sockaddr)) < 0 ) {
        perror("Error binding socket!");
        exit(1);
    } else {
        printf("I'm bound. serverAddr:%ld serverSockFd: %d\n", 
                localAddr.sin_addr.s_addr, serverSockFd);
    }

    /* listen for incoming connection request */
    if( listen( serverSockFd, 1 ) < 0 ) {
        perror("Error with listen()");
        exit(1);
    }

    /* accept incoming connections...*/
    printf("Ready for incoming connections...\n");
    /* FIXME for future, use select ..as this is blocking by nature */
    if( (clientSockFd = accept( serverSockFd, (struct sockaddr * ) &clientAddr, &cAddrLen) ) < 0 ) {
        perror("Error accepting incoming connections");
        exit(1);
    } else {
        /* receive data from client */
        if( recv( serverSockFd, dataBuffer, sizeof(dataBuffer), 0 ) < 0 ) {
            perror("Error receiving data from client");
        } else {
            printf("Client sent:\n '%s'\n", dataBuffer);
        }

        /* send data to client */
        if( send( serverSockFd, "Message from server\n", strlen("Message from server\n")+1, 0) < 0 ) {
            perror("Error sending data");
        } else {
            printf("Message sent to client: %d\n", clientSockFd);
        }

    }

    return 0;
}
