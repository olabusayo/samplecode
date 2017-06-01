#include "Server.h"

int main(int argc, char * argv[]) {

    //int clientSockFd = 0,
	int retval = 0;
	//,        nBytes = 0;
    //socklen_t clientAddrLen = sizeof(struct sockaddr_in);
    char input[INPUT_SIZE] = {0},
    		//*dynamicDataBuffer = NULL,
			localAddrIp[IPV4LEN] = {0},
			//clientAddrIp[IPV4LEN] = {0},
			errorString[INPUT_SIZE] = {0};
    struct sockaddr_in localAddr = {0};//, clientAddr = {0};
    unsigned int localAddrPort = 0;//, clientAddrPort = 0;

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
        Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
    }
    printf("localAddr port & addr: %d, %s\n", localAddrPort, localAddrIp);
    
    // create server socket
    //Not adding it to list of sockets because we don't want to close it, unless explicit
    if ( ( serverSockFd = Utils_createReuseableSocket(AF_INET, SOCK_STREAM, 0, &listOfOpenSockets) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error creating server socket: %s", strerror(errno));
        Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
    }

    // bind to local address
    if( bind(serverSockFd, (struct sockaddr *) &localAddr, sizeof(struct sockaddr_in) ) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error binding to local address: %s", strerror(errno));
        Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
    } else {
        printf("I (Socket %d) am bound to addr: %s on port %d\n",
        		serverSockFd, localAddrIp, localAddrPort );
    }

    // make server socket passive
    if( listen(serverSockFd, 3) < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error making server socket passive: %s", strerror(errno));
        Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
    }
    printf("Socket %d is passive...\nEnter Ctrl-C to stop server\n\n", serverSockFd);

    Server_acceptClientConnection(NULL);

    Utils_doToAllSockets(&listOfOpenSockets, &closeFuncParams);
    printf("Thank you. Goodbye!\n");
    return 0;
}

void Server_communicateWithClient(void *clientInfoArg) {
	char *dynamicDataBuffer = NULL;
	int recvBytes = 0;
	ClientSocketInfo *clientSockInfo = NULL;
	clientSockInfo = (ClientSocketInfo *) clientInfoArg;

	printf("Communicating with client %d with info stored at %p\n\n", clientSockInfo->clientSocketFd, clientSockInfo );

	while( (recvBytes = Utils_receiveDataFromSocket(clientSockInfo->clientSocketFd, &dynamicDataBuffer, 0) ) > 0 ) {
		printf("%d bytes received from Client %d.\n", recvBytes, clientSockInfo->clientSocketFd);
		// send data to client
		Server_sendDataToClient(clientSockInfo, &dynamicDataBuffer, strlen(dynamicDataBuffer)+1);

	}

	if( recvBytes == 0 ) {
		printf("Client %d from port %d, addr %s closed the connection.\n",
				clientSockInfo->clientSocketFd, clientSockInfo->clientAddrPort, clientSockInfo->clientAddrIp);
	} else {
		printf("Error receiving data from client %d from port %d, addr %s: %s \n",
				clientSockInfo->clientSocketFd, clientSockInfo->clientAddrPort, clientSockInfo->clientAddrIp, strerror(errno));
	}

	closeFuncParams.socketFd = clientSockInfo->clientSocketFd;
	Utils_freePointer((void **) &clientInfoArg);
	Utils_freePointer((void **) &dynamicDataBuffer);
	clientSockInfo = NULL;
	Utils_doToSocket(&closeFuncParams, &listOfOpenSockets);
}

void Server_sendDataToAllClientsExceptSender(int sendingSocketFd, char ** dataBuffer, int dataBufferLen, SocketList listOfOpenSockets) {
	SocketElement *socket = NULL;
	LIST_FOREACH(socket, &listOfOpenSockets->head, socketElements ) {
		if(socket->socketFd != sendingSocketFd && socket->socketFd != serverSockFd) {
			Server_sendDataToClient(socket->socketFd, dataBuffer, dataBufferLen);
		}
	}
}

void Server_sendDataToClient(int clientSocketFd, char **dynamicDataBuffer, int dataBufferLen) {
	int sendBytes = 0;
	char errorString[INPUT_SIZE] = {0};
	if( (sendBytes = send(clientSocketFd, *dynamicDataBuffer, dataBufferLen, 0 ) ) <= 0 ) {
		memset(errorString, '\0', sizeof(errorString));
		snprintf(errorString, sizeof(errorString), "Error sending data to client %d: %s \n",
				clientSocketFd,  strerror(errno));
		Utils_freePointer((void **)dynamicDataBuffer);
		Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
	} else {
		printf("%d bytes sent to Client %d.\n", sendBytes, clientSocketFd);
	}
}

void Server_acceptClientConnection(void * arg) {
    char errorString[INPUT_SIZE] = {0};
    struct sockaddr_in clientAddr = {0};
    socklen_t clientAddrLen = sizeof(struct sockaddr_in);
    ClientSocketInfo *clientSockInfo = NULL;
    int retval = 0, clientSocketFd = 0;
    pthread_t commPth;


    //return;

    while( ( clientSocketFd = accept(serverSockFd, (struct sockaddr *) &clientAddr, &clientAddrLen) ) > 0 ) {
        clientSockInfo = (ClientSocketInfo *)calloc(1, sizeof(ClientSocketInfo));
    	printf("Allocating memory for client info @ %p\n", clientSockInfo );

    	clientSockInfo->clientSocketFd = clientSocketFd;
    	UtilsLinkedList_addToListOfSockets(&listOfOpenSockets, clientSockInfo->clientSocketFd);
    	clientSockInfo->clientAddrPort = ntohs(clientAddr.sin_port);
    	strncpy(clientSockInfo->clientAddrIp, inet_ntoa(clientAddr.sin_addr), IPV4LEN-1);
    	clientSockInfo->clientAddrIp[IPV4LEN-1] = '\0';

    	printf("Accepted connection to client %d from addr: %s port %d\n",
    			clientSockInfo->clientSocketFd, clientSockInfo->clientAddrIp, clientSockInfo->clientAddrPort );

    	//communicate with client
    	//Server_communicateWithClient(&clientSockInfo);
        if( (retval = pthread_create(&commPth, NULL, (void *) &Server_communicateWithClient, (void *)clientSockInfo )) != 0 ) {
        	memset(errorString, '\0', sizeof(errorString));
            snprintf(errorString, sizeof(errorString), "Error creating thread: %s", strerror(retval));
            Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
        } else {
        	printf("Thread %ld to communicate with %d is spawned...\n", pthread_idgen(commPth), clientSockInfo->clientSocketFd);
        }


    	printf("Socket %d is passive...\nEnter Ctrl-C to stop server\n\n", serverSockFd);
    }

    if( clientSockInfo->clientSocketFd < 0 ) {
    	memset(errorString, '\0', sizeof(errorString));
        snprintf(errorString, sizeof(errorString), "Error accepting client connection: %s \n", strerror(errno));
        Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, errorString, EXIT_FAILURE);
    }

}

void Server_handleSignalInterrupt(int signum) {
	char msg[INPUT_SIZE] = {0};
	snprintf(msg, sizeof(msg), "Received Signal: %s\n", strsignal(signum));
	Utils_doToSocketsAndExit(&closeFuncParams, &listOfOpenSockets, msg, EXIT_SUCCESS );
}
