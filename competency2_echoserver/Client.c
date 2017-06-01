#include "Client.h"

int main(int argc, char *argv[]) {

    int serverSockFd = 0, retval = 0,
        nBytes = 0;
    //socklen_t serverAddrLen = 0;
    unsigned int serverAddrPort = 0;
    char input[INPUT_SIZE] = {0}, *dynamicDataBuffer = NULL,
    		serverAddrIp[IPV4LEN] = {0}, errorString[INPUT_SIZE] = {0};
    struct sockaddr_in serverAddr = {0};
    struct sigaction newSigIntAction = {0};
    newSigIntAction.sa_handler = Client_handleSignalInterrupt;
	sigaction(SIGINT, &newSigIntAction, NULL);

	UtilsLinkedList_newListOfSockets(&listOfOpenSockets);


    if( argc == 2 ) {
    	printf("Usage:%s ip_address port. Ignoring input %s\n", argv[0], argv[1]);
    }

    // validate and store ip address & port
    if( argc != 3 || Utils_validateAndStoreIp(argv[1], &serverAddr) != VALID ) {
    	do{
    		Utils_getIpUserInput(input, INPUT_SIZE);
    	} while( Utils_validateAndStoreIp(input, &serverAddr) != VALID );
    }
    strncpy(serverAddrIp, inet_ntoa(serverAddr.sin_addr), IPV4LEN-1);
    serverAddrIp[IPV4LEN-1] = '\0';
    printf("Address entered: %s\n", serverAddrIp);

    if( argc != 3 || Utils_validateAndStorePort(argv[2], &serverAddr) != VALID ) {
    	do{
    		Utils_getPortUserInput(input, INPUT_SIZE);
    	} while( Utils_validateAndStorePort(input, &serverAddr) != VALID );
    }
    serverAddrPort = ntohs(serverAddr.sin_port);
	printf("Port entered: %d\n\n", serverAddrPort);

    // build server address: fill in port, verify important components
    if( (retval = Utils_isValidInternetAddrStruct(serverAddr)) != VALID ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Issue with SockAddr: Error %d. Exiting\n", retval);
        Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }

    // create server socket
    if( ( serverSockFd = Utils_createReuseableSocket(AF_INET, SOCK_STREAM, 0, &listOfOpenSockets) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error creating client socket: %s\n", strerror(errno));
        Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    }

    // connect to server address
    if( connect(serverSockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error connecting to server: %s\n", strerror(errno));
        Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
    } else {
        printf("Connected to server socket %d at addr: %s on port %d\n",
        		serverSockFd, serverAddrIp, serverAddrPort);
    }
    
    do {
		//get User Input
		do {
			retval = Utils_getDataUserInput( &dynamicDataBuffer );
			if( retval == -1 ) {
				memset(errorString, '\0', sizeof(errorString));
				snprintf(errorString, sizeof(errorString), "Exiting: %s\n", strerror(errno));
				Utils_freePointer((void **)&dynamicDataBuffer);
				Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
			}
		} while ( dynamicDataBuffer == NULL || dynamicDataBuffer[0] == '\0' || retval == 0 );

		// send data to server
		//printf("Send data to server\n");
		if( (nBytes = send(serverSockFd, dynamicDataBuffer, strlen(dynamicDataBuffer)+1, 0) ) <= 0 ) {
			memset(errorString, '\0', sizeof(errorString));
			snprintf(errorString, sizeof(errorString), "Error sending data to server: %s\n", strerror(errno));
			Utils_freePointer((void **)&dynamicDataBuffer);
			Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
		} else {
			printf("%d bytes sent.\n", nBytes);
		}
		//done with dynamicDataBuffer; Reset
		memset(dynamicDataBuffer, '\0', strlen(dynamicDataBuffer)+1);


		//receive data from server
		//printf("Receive data from server\n");
		if( (nBytes = Utils_receiveDataFromSocket(serverSockFd, &dynamicDataBuffer) ) <= 0 ) {
			memset(errorString, '\0', sizeof(errorString));
			snprintf(errorString, sizeof(errorString), "Error receiving data from server from port %d, addr %s: %s \n",
					serverAddrPort, serverAddrIp, strerror(errno));
			Utils_freePointer((void **)&dynamicDataBuffer);
			Utils_shutdownSocketsAndExit(&listOfOpenSockets, errorString, EXIT_FAILURE);
		} else {
			printf("%d bytes received.\nMessage:\n'%s'\n", nBytes, dynamicDataBuffer);
		}/**/

		//free memory
		Utils_freePointer((void **)&dynamicDataBuffer);

    } while( Utils_askUserForYesNoInput("\nTo send more data to server enter Y, else enter N") == 1 );

    Utils_shutdownAllSockets(&listOfOpenSockets, SHUT_RDWR);
    printf("Thank you. Goodbye!\n");
    return 0;
}

void Client_handleSignalInterrupt(int signum) {
	char errMsg[INPUT_SIZE] = {0};
	snprintf(errMsg, sizeof(errMsg), "Received Signal: %s.\n", strsignal(signum));
	Utils_shutdownSocketsAndExit(&listOfOpenSockets, errMsg, EXIT_SUCCESS );
}
