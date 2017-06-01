#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main( int argc, char *argv[] ) {

    int clientSockFd = 0, serverSockFd, retval = 0, nBytes = 0;
    struct sockaddr serverAddr;
    struct addrinfo sHintsInfo, *sResultsInfo, *serverAddrInfo;
    char dataBuffer[256];
    char *errPtr = NULL;
    

    if( argc != 3 ) {
        fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
        exit(1);
    }

    char *serverHostname = argv[1];
    char *serverPort = argv[2];

    /* Do port validation */
    Utils_stringToLong(serverPort, &errPtr);
    if( errPtr != NULL && *errPtr != '\0' ) {
        fprintf(stderr, "Port provided is invalid: %s\n", serverPort);
        exit(1);
    }

    /* Initialize Structures*/
    memset(&serverAddr, '\0', sizeof(serverAddr));
    memset(dataBuffer, '\0', sizeof(dataBuffer));
    memset(&sHintsInfo, '\0', sizeof(sHintsInfo));
    memset(sResultsInfo, '\0', sizeof(sResultsInfo));
    memset(serverAddrInfo, '\0', sizeof(serverAddrInfo));

    /* call new socket */
    clientSockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    /* get address info from hostname */
    /* do hostname validation */
    if( (retval = getaddrinfo(serverHostname, serverPort, &sHintsInfo, &sResultsInfo)) != 0 ) {
        fprintf(stderr, "Error resolving hostname provided: %s\n", gai_strerror(retval));
        exit(1);
    }
    
    /* Iterate through address list till connnection is possible, that will be our
     * server info */
    for( serverAddrInfo = sResultsInfo; serverAddrInfo != NULL ; serverAddrInfo = serverAddrInfo->ai_next ) {
       serverSockFd =  socket( serverAddrInfo->ai_family, serverAddrInfo->ai_socktype, serverAddrInfo->ai_protocol);

       printf("Checking serverAddr:%ld serverSockFd: %d\n", 
               serverAddrInfo->ai_addr->sa_data, serverSockFd);
       if( serverSockFd < 0 ) {
           continue;
       }
       
       if ( connect( serverSockFd, serverAddrInfo->ai_addr, serverAddrInfo->ai_addrlen ) == 0 ) {
           printf("Connected serverSockFd %d to serverAddr:%ld \n", 
               serverSockFd, serverAddrInfo->ai_addr->sa_data);
           break;
       }

       close(serverSockFd);
    }

    freeaddrinfo(sResultsInfo);

    if( serverAddrInfo == NULL ) {
        fprintf(stderr, "Could not find any server to connect to\n");
        exit(1);
    }


    /* populate serverAddr */
    //serverAddr = *(serverAddrInfo->ai_addr);

    /* connect to server socket */
    /*if( connect( clientSockFd, &serverAddr, sizeof(struct sockaddr) ) < 0 ) {
        perror("Error connecting to server");
        exit(1);
    } else {
    */
    /* send data to server */
    printf("Sending data to serverSockFd %d\n", serverSockFd);
    if( (nBytes = send( clientSockFd, "I'm me from Planet Client\n", strlen("I'm me from Planet Client\n")+1, 0)) < 0 ) {
        perror("Error sending data");
        exit(1);
    } else {
       printf("Sent %d bytes to server %d\n", nBytes, serverSockFd);
    }

    nBytes = 0; 
    
    /* receive data from server */
    if( (nBytes = recv( clientSockFd, dataBuffer, sizeof(dataBuffer), 0)) < 0 ) {
        perror("Error receiving data");
    } else {
        printf("Message of %d bytes from server:\n'%s'\n", nBytes, dataBuffer);
    }
    //}

    /* end connection */
    if ( close(serverSockFd) < 0 ) {
        fprintf(stderr, "Error closing socket %d", serverSockFd );
    } else {
        printf("Socket %d close successfully\n", serverSockFd);
    }

    return 0;
}
