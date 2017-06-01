/*
 * Client.h
 *
 *  Created on: May 9, 2017
 *      Author: root
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include "Utils.h"

void Client_handleSignalInterrupt(int signum);

SocketList listOfOpenSockets = {0};

#endif /* CLIENT_H_ */
