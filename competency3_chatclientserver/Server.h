/*
 * Server.h
 *
 *  Created on: May 9, 2017
 *      Author: root
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "Utils.h"

typedef struct clientSocketInfo {
	int clientSocketFd;
	char clientAddrIp[IPV4LEN];
	int clientAddrPort;
	unsigned long pthread_id;
} ClientSocketInfo;
void Server_handleSignalInterrupt(int signum);
void Server_acceptClientConnection(void * arg);
void Server_communicateWithClient(void* clientInfoArg);
void Server_sendDataToClient(ClientSocketInfo *clientSockInfo, char **dataBuffer, int dataBufferLen);

SocketList listOfOpenSockets = {0};
int serverSockFd = 0;
EndSocketParams closeFuncParams = {"close", 0, 0};

#endif /* SERVER_H_ */
