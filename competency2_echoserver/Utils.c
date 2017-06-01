#include "Utils.h"


void Utils_flushStream(FILE *stream) {
    char c;
    //printf("Flushing stream\n");
    while( (c = getc(stream)) != '\n' && c != EOF ) {
    }
}

void Utils_getLine(char * str, int size) {
	char * fgetsStatus;
	fgetsStatus = fgets(str, size, stdin);
   if( strlen(str) > 0 && str[strlen(str) - 1] != '\n') {
       Utils_flushStream(stdin);
   } else if( fgetsStatus != 0 && str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
	}
}

int Utils_getInput(char ** inputStr) {
	char * fgetsStatus = NULL, str[INPUT_SIZE] = {0},
			*newBufferPtr = NULL;
	int totalSize = 0, charsToGrab = 0;

	while( (totalSize < (MAX_INPUT_TCP-1)) && (fgetsStatus = fgets(str, INPUT_SIZE, stdin)) != NULL ) {

		totalSize += strlen(str);

		if( totalSize >= MAX_INPUT_TCP) {

			totalSize -= strlen(str);
			charsToGrab = ((MAX_INPUT_TCP - 1) - totalSize) < strlen(str) ? ((MAX_INPUT_TCP - 1) - totalSize) : strlen(str);
			totalSize += charsToGrab;
			printf("Input is approaching max length for TCP Transfer.\n");
			if(strlen(str) > charsToGrab) {
				printf("Discarding rest of input starting at the \n'%s' in '%s'\n", &(str[charsToGrab]), str);
			}

			if( (newBufferPtr = realloc(*inputStr, totalSize+1 )) != NULL ) {
				*inputStr = newBufferPtr;
				newBufferPtr = NULL;
				//initialize newly added memory
				memset(&((*inputStr)[totalSize-charsToGrab]), '\0', charsToGrab+1);
				//concatenate contents of dataBuffer to dynamicDataBuffer
				memcpy(&((*inputStr)[totalSize-charsToGrab]), (void *)str, charsToGrab);

				//replace newline with string terminator
				if( (*inputStr)[strlen(*inputStr) - 1] == '\n') {
					(*inputStr)[strlen(*inputStr) - 1] = '\0';
				}
			}
			if( strlen(str) > 0 && str[strlen(str) - 1] != '\n') {
				Utils_flushStream(stdin);
			}
			break;
		} else {
			if( (newBufferPtr = realloc(*inputStr, totalSize+1 )) != NULL ) {
				*inputStr = newBufferPtr;
				newBufferPtr = NULL;
				//initialize newly added memory
				memset(&((*inputStr)[totalSize-strlen(str)]), '\0', strlen(str)+1);
				//concatenate contents of dataBuffer to dynamicDataBuffer
				memcpy(&((*inputStr)[totalSize-strlen(str)]), (void *)str, strlen(str));

				//replace newline with string terminator
				if( (*inputStr)[strlen(*inputStr) - 1] == '\n') {
					(*inputStr)[strlen(*inputStr) - 1] = '\0';
				}
			} else {
				fprintf(stderr, "realloc failed to reallocate variable to size %d bytes: %s\n", totalSize+1, strerror(errno));
				printf("Freeing Variable; Current contents:\n'%s'\n", *inputStr);
				Utils_freePointer((void **)inputStr);
				return(errno);
			}

			//no more messages to be sent
			if( str[strlen(str) - 1] == '\n' ) {
				break;
			}
		}
	}

	//counting terminating null
	totalSize++;
	return totalSize;
}

void Utils_getIpUserInput(char * input, int size) {
	printf("Please enter in IPv4 IP Address: ");
	Utils_getLine(input, size);
}

void Utils_getPortUserInput(char * input, int size) {
	printf("Please enter in valid port: ");
	Utils_getLine(input, size);
}

int Utils_validateAndStoreIp( const char * ip, struct sockaddr_in * serverAddr) {
    int retval = INVALID_INPUT;

    if( (retval = inet_aton(ip, &(serverAddr->sin_addr))) == 1 ) {//successful
        retval = VALID;
        serverAddr->sin_family = AF_INET;
    } else {
    	retval = INVALID_INPUT;
    	printf("Invalid IP entered: %s\n", ip);
    }
    
    return retval;
}

int Utils_validateAndStorePort(char * port, struct sockaddr_in * serverAddr) {
    // port can be between 1024 and 65535; anything lower is well known
    // attempt to convert to unsigned long int
    char * errPtr = NULL;
    unsigned long tempPort = 0;
    int retval = 0;

    tempPort = strtoul(port, &errPtr, 10);
    if( errPtr != NULL && *errPtr != '\0') {
        //validation failed
        fprintf(stderr, "Invalid input encountered: %s\n", errPtr);
        retval = INVALID_INPUT;
    } else if (tempPort <= MINPORT || tempPort > MAXPORT ) {
        //conversion successful but outside of acceptable port numbers
        fprintf(stderr, "Invalid port entered: %ld\n", tempPort);
        retval = INVALID_PORT;
    } else {
        //acceptable port
        //convert to int; convert to network byte order
        serverAddr->sin_port = htons(atoi(port));
    }

    return retval;
}

int Utils_isValidInternetAddrStruct(struct sockaddr_in myAddr) {
    int retval = 0;

    if( myAddr.sin_family != AF_INET ) {
        fprintf(stderr, "Issue with IP Address family: %d.\n", myAddr.sin_family);
        retval = INVALID_INET_FAMILY;
    } else if( myAddr.sin_addr.s_addr == '\0') {
        fprintf(stderr, "Issue with IP Address: %ld.\n", (long) myAddr.sin_addr.s_addr);
        retval = INVALID_IP;
    } else if (myAddr.sin_port <= MINPORT || myAddr.sin_port > MAXPORT ) {
        retval = INVALID_PORT;
    }
    
    return retval;
}

int Utils_getDataUserInput(char ** dataInput) {
	int retval = 0;
	printf("Please enter data to send to client:\n");
	if( (retval = Utils_getInput(dataInput)) < 0 ) {
		fprintf(stderr, "Issue getting input: %s\n", strerror(errno));
	}
	return retval;
}

int Utils_askUserForYesNoInput(char * question) {
   char in[INPUT_SIZE] = {0};
   int response = -1;

   do {
       printf("%s: ", question);
       Utils_getLine(in, INPUT_SIZE);

       if( strlen(in) != 1 ) {
    	   response = -1;
       } else if( toupper(in[0]) == 'Y' ) {
           response = 1;
       } else if( toupper(in[0]) == 'N' ) {
          response =  0;
       }
    } while( response != 1 && response != 0 );

   return response;
}

int Utils_receiveDataFromSocket(int clientSockFd, char ** dynamicDataBuffer) {

	int nBytes = 0, bytesReceived = 0;
	char dataBuffer[PEEKQUANTITY] = {0}, *newBufferPtr = NULL;

	while( (bytesReceived = recv(clientSockFd, dataBuffer, PEEKQUANTITY, 0)) > 0
			&& dataBuffer[0] != '\0' ) {

		nBytes += bytesReceived;

		//allocate memory of size nBytes + 1 for null terminating \0
		if( (newBufferPtr = realloc(*dynamicDataBuffer, nBytes+1 )) != NULL ) {//if successful
			*dynamicDataBuffer = newBufferPtr;
			newBufferPtr = NULL;
			//initialize newly added memory
			memset(&((*dynamicDataBuffer)[nBytes-bytesReceived]), '\0', bytesReceived+1);
			//concatenate contents of dataBuffer to dynamicDataBuffer
			memcpy(&((*dynamicDataBuffer)[nBytes-bytesReceived]), (void *)dataBuffer, bytesReceived);
		} else {
			fprintf(stderr, "Realloc Failed to reallocate variable Data Buffer to size %d bytes: %s\n", nBytes, strerror(errno));
			printf("Freeing Variable; Current contents:\n'%s'\n", *dynamicDataBuffer);
			Utils_freePointer((void **)dynamicDataBuffer);
			return(-1);
		}

		//rest of message was received in previous call
		if( bytesReceived < PEEKQUANTITY || (bytesReceived == PEEKQUANTITY && dataBuffer[PEEKQUANTITY-1] == '\0'))  {
			break;
		}
	}

	// To properly mimic recv's actions, will not count terminating null byte

	return nBytes;

}

int Utils_createSocket(int family, int sockType, int sockProtocol, SocketList *lOpenSockets ) {
	int sockFd = 0;

	if ( ( sockFd = socket(family, sockType, sockProtocol ) ) < 0 ) {
		sockFd = -1;
	}

	if( lOpenSockets != NULL) {
		UtilsLinkedList_addToListOfSockets(lOpenSockets, sockFd);
	}

	return sockFd;
}

int Utils_createReuseableSocket(int family, int sockType, int sockProtocol, SocketList *lOpenSockets ) {
	int sockFd = 0, opt = 1;

	if( (sockFd = Utils_createSocket(family, sockType, sockProtocol, lOpenSockets)) > 0 ) {
		setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	}

	return sockFd;
}

int Utils_closeSocket(int socketFd, SocketList *lSockets) {
	int retval = close(socketFd);
	if( retval == 0 ) {
		printf("Socket %d closed successfully.\n", socketFd);
	} else {
		fprintf(stderr, "Issues closing socket %d : %s (%d)\n", socketFd, strerror(errno), errno);
	}
	if( lSockets != NULL ) {
		UtilsLinkedList_removeFromListOfSockets(lSockets, socketFd);
	}

	return retval;
}

int Utils_shutdownSocket(int socketFd, SocketList *lSockets, int how) {
	int retval = shutdown(socketFd, how);
	if( retval == 0 ) {
		printf("Socket %d shutdown successfully.\n", socketFd);
	} else {
		fprintf(stderr, "Issues shutting down socket %d : %s (%d)\n", socketFd, strerror(errno), errno);
	}
	if( lSockets != NULL ) {
		UtilsLinkedList_removeFromListOfSockets(lSockets, socketFd);
	}

	return retval;
}

int Utils_closeAllSockets(SocketList *lSockets) {
	int sockFd = 0, count = 0;
	while ( !LIST_EMPTY(&lSockets->head) && (sockFd = lSockets->head.lh_first->socketFd ) > 0 ) {
		printf("\nClosing socket %d\n", sockFd);
		Utils_closeSocket( sockFd, lSockets);
		count++;
	}

	return count;
}

int Utils_shutdownAllSockets(SocketList *lSockets, int how) {
	int sockFd = 0, count = 0;
	while ( !LIST_EMPTY(&lSockets->head) && (sockFd = lSockets->head.lh_first->socketFd) > 0 ) {
		printf("\nShutting down socket %d\n", sockFd);
		Utils_shutdownSocket( sockFd, lSockets, how);
		count++;
	}

	return count;
}

void Utils_exitWithMessage(char * errorMessage, int exitConst) {
	if( exitConst != EXIT_SUCCESS ) {//i.e you want to exit on error
		fprintf(stderr, errorMessage);
	} else {
		printf("\n%sThank you. Goodbye!\n", errorMessage);
	}

	exit(exitConst);
}

void Utils_shutdownSocketsAndExit(SocketList *lSockets, char * errorMessage, int exitConst) {
	Utils_shutdownAllSockets(lSockets, SHUT_RDWR);
	Utils_exitWithMessage(errorMessage, exitConst);
}

void Utils_closeSocketsAndExit(SocketList *lSockets, char * errorMessage, int exitConst) {
	Utils_closeAllSockets(lSockets);
	Utils_exitWithMessage(errorMessage, exitConst);
}

void Utils_freePointer(void ** addrToPtr) {
	if( *addrToPtr != NULL ) {
		free(*addrToPtr);
		*addrToPtr = NULL;
	}
}
