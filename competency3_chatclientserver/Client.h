/*
 * Client.h
 *
 *  Created on: May 9, 2017
 *      Author: root
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include "Utils.h"
#include <pthread.h>

void Client_handleSignalInterrupt(int signum);

SocketList listOfOpenSockets = {0};
//pthread_mutex_t mutexLock = 0;
EndSocketParams params = {"shutdown", 0, SHUT_WR};

#endif /* CLIENT_H_ */
