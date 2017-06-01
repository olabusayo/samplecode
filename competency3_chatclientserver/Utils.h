#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include "UtilsLinkedList.h"

/* FIXME enum? */
#define VALID 0
#define INVALID_INPUT -1
#define INVALID_IP -2
#define INVALID_INET_FAMILY -3
#define INVALID_PORT -4

#define INPUT_SIZE 256
#define PEEKQUANTITY 1000
#define IPV4LEN 16
#define MINPORT 1024
#define MAXPORT 65535
#define MAX_INPUT_TCP 4095

#define pthread_idgen(num) ((num) % 3000)
#define timestamp_print(string) printf("%s %s: %s", __DATE__, __TIME__, (string))
#define assign_var_and_pass_as_arg(vararg, varvalue, arg) \
	(((vararg) = (varvalue)) == 1 ? arg : arg)

typedef struct endSocketParams {
	char actionType[9];
	int socketFd;
	int shutdownHow;
} EndSocketParams;


extern int errno;


void Utils_flushStream(FILE *stream);
void Utils_getLine(char * str, int size);
void Utils_getIpUserInput(char * input, int size);
void Utils_getPortUserInput(char * input, int size);
int Utils_validateAndStoreIp( const char * ip, struct sockaddr_in * serverAddr);
int Utils_validateAndStorePort(char * port, struct sockaddr_in * serverAddr);
int Utils_isValidInternetAddrStruct(struct sockaddr_in myAddr);
int Utils_getInput(char ** inputStr);
int Utils_getDataUserInput(char ** dataInput);
int Utils_askUserForYesNoInput(char * question);
int Utils_createSocket(int family, int sockType, int sockProtocol, SocketList *lOpenSockets );
int Utils_createReuseableSocket(int family, int sockType, int sockProtocol, SocketList * lOpenSockets );
int Utils_receiveDataFromSocket(int clientSockFd, char ** dynamicDataBuffer, int recvFlag);
int Utils_doToSocket(EndSocketParams *params, SocketList *lSockets);
int Utils_doToAllSockets(SocketList *lSockets, EndSocketParams *params);
void Utils_exitWithMessage(char * errorMessage, int exitConst);
void Utils_doToSocketsAndExit(EndSocketParams *params, SocketList *lSockets, char * errorMessage, int exitConst);
//void Utils_handleSignalInterrupt(int signum);
void Utils_freePointer(void ** addrToPtr);

#endif /*UTILS_H*/
