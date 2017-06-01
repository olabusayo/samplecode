/*
 * UtilsLinkedList.h
 *
 *  Created on: May 3, 2017
 *      Author: root
 */

#ifndef UTILSLINKEDLIST_H_
#define UTILSLINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <string.h>

typedef struct socketElement {
		int socketFd;
		LIST_ENTRY(socketElement) socketElements;
} SocketElement;

typedef LIST_HEAD(socketListHead, socketElement)
		SocketListHead;

typedef struct socketList {
	int size;
	int initialized;
	SocketListHead head;
} SocketList;

SocketList* UtilsLinkedList_newListOfSockets(SocketList *sList);
void UtilsLinkedList_addToListOfSockets(SocketList *sList, int sockfd);
void UtilsLinkedList_removeFromListOfSockets(SocketList *sList, int sockfd);
void UtilsLinkedList_removeAllFromListOfSockets(SocketList *sList);
void UtilsLinkedList_printListOfSockets(SocketList *sList);

#endif /* UTILSLINKEDLIST_H_ */
