/*
 * Server.h
 *
 *  Created on: May 9, 2017
 *      Author: root
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "Utils.h"

void Server_handleSignalInterrupt(int signum);

SocketList listOfOpenSockets = {0};

#endif /* SERVER_H_ */
