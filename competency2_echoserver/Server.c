#include "Server.h"

int main(int argc, char * argv[]) {

    int serverSockFd = 0, clientSockFd = 0, retval = 0,
        nBytes = 0;
    socklen_t clientAddrLen = 0;
    char input[INPUT_SIZE] = {0},
    		*dynamicDataBuffer = NULL,
			localAddrIp[IPV4LEN] = {0}, clientAddrIp[IPV4LEN] = {0},
			errorString[INPUT_SIZE] = {0};
    struct sockaddr_in localAddr = {0}, clientAddr = {0};
    unsigned int localAddrPort = 0, clientAddrPort = 0;

    struct sigaction newSigIntAction = {0};
    newSigIntAction.sa_handler = Server_handleSignalInterrupt;
	sigaction(SIGINT, &newSigIntAction, NULL);

    UtilsLinkedList_newListOfSockets(&listOfOpenSockets);


    if( argc == 2 ) {
    	printf("Usage:%s ip_address port. Ignoring input %s\n", argv[0], argv[1]);
    }

    // validate and store ip address & port
    if( argc != 3 || Utils_validateAndStoreIp(argv[1], &localAddr) != VALID ) {
    	do{
    		Utils_getIpUserInput(input, INPUT_SIZE);
    	} while( Utils_validateAndStoreIp(input, &localAddr) != VALID );
    }
    strncpy(localAddrIp, inet_ntoa(localAddr.sin_addr), IPV4LEN-1);
    localAddrIp[IPV4LEN-1] = '\0';
    printf("Address entered: %s\n", localAddrIp);

    if( argc != 3 || Utils_validateAndStorePort(argv[2], &localAddr) != VALID ) {
    	do{
    		Utils_getPortUserInput(input, INPUT_SIZE);
    	} while( Utils_validateAndStorePort(input, &localAddr) != VALID );
    }
    localAddrPort = ntohs(localAddr.sin_port);
	printf("Port entered: %d\n\n", localAddrPort);

    // bind to address from user input
    //make sure localAddr is well populated  
    if( Utils_isValidInternetAddrStruct(localAddr) != VALID ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Issue with SockAddr: %d. Exiting\n", retval);
        Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }
    printf("localAddr port & addr: %d, %s\n", localAddrPort, localAddrIp);
    
    // create server socket
    //Not adding it to list of sockets because we don't want to close it, unless explicit
    if ( ( serverSockFd = Utils_createReuseableSocket(AF_INET, SOCK_STREAM, 0, &listOfOpenSockets) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error creating server socket: %s", strerror(errno));
        Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }

    // bind to local address
    if( bind(serverSockFd, (struct sockaddr *) &localAddr, sizeof(struct sockaddr_in) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error binding to local address: %s", strerror(errno));
        Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    } else {
        printf("I (Socket %d) am bound to addr: %s on port %d\n",
        		serverSockFd, localAddrIp, localAddrPort );
    }

    // make server socket passive
    if( listen(serverSockFd, 3) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error making server socket passive: %s", strerror(errno));
        Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }
    printf("Socket %d is passive...\nEnter Ctrl-C to stop server\n\n", serverSockFd);

    // accept client connection
    clientAddrLen = sizeof(struct sockaddr_in);
    while( ( clientSockFd = accept(serverSockFd, (struct sockaddr *) &clientAddr, &clientAddrLen) ) > 0 ) {
    	UtilsLinkedList_addToListOfSockets(&listOfOpenSockets, clientSockFd);
    	strncpy(clientAddrIp, inet_ntoa(clientAddr.sin_addr), IPV4LEN-1);
    	clientAddrIp[IPV4LEN-1] = '\0';
    	clientAddrPort = ntohs(clientAddr.sin_port);
    	printf("Accepted connection to client %d from addr: %s port %d\n\n",
    			clientSockFd, clientAddrIp, clientAddrPort );

    	do {
			// receive data from client
    		//printf("Receive data from client\n");
			if( (nBytes = Utils_receiveDataFromSocket(clientSockFd, &dynamicDataBuffer) ) <= 0 ) {
				if( errno == 0 ) {
					printf("Client %d from port %d, addr %s closed the connection.\n",
							clientSockFd, clientAddrPort, clientAddrIp);
				} else {
					printf("Error receiving data from client from port %d, addr %s: %s \n",
						clientAddrPort, clientAddrIp, strerror(errno));
				}
				break;
			} else {
				printf("%d bytes received.\n", nBytes);
			}

			// send data to client
			//printf("Send data to client\n");
			if( (nBytes = send(clientSockFd, dynamicDataBuffer, strlen(dynamicDataBuffer)+1, 0 ) ) <= 0 ) {
				memset(errorString, '\0', sizeof(errorString));
				snprintf(errorString, sizeof(errorString), "Error sending data to client from port %d, addr %s: %s \n",
						clientAddrPort, clientAddrIp, strerror(errno));
				Utils_freePointer((void **)&dynamicDataBuffer);
				Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
			} else {
				printf("%d bytes sent.\n", nBytes);
			}

	    	//free memory so it's ready to accept more should the client send more
	    	Utils_freePointer((void **)&dynamicDataBuffer);
	    	printf("Waiting on data from Socket %d...\n\n", clientSockFd);
    	} while( recv(clientSockFd, input, sizeof(input), MSG_PEEK) > 0  );


    	Utils_freePointer((void **)&dynamicDataBuffer);
    	// close client socket
    	Utils_closeSocket(clientSockFd, &listOfOpenSockets);

    	printf("Socket %d is passive...\nEnter Ctrl-C to stop server\n\n", serverSockFd);
    }

    if( clientSockFd < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error accepting client connection: %s \n", strerror(errno));
        Utils_closeSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }
    
    Utils_closeAllSockets(&listOfOpenSockets);
    printf("Thank you. Goodbye!\n");
    return 0;
}

void Server_handleSignalInterrupt(int signum) {
	char msg[INPUT_SIZE] = {0};
	snprintf(msg, sizeof(msg), "Received Signal: %s\n", strsignal(signum));
	Utils_closeSocketsAndExit(&listOfOpenSockets, msg, EXIT_SUCCESS );
}
