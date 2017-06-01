/*
 * UtilsLinkedList.c
 *
 *  Created on: May 3, 2017
 *      Author: root
 */
#include "UtilsLinkedList.h"

SocketList* UtilsLinkedList_newListOfSockets(SocketList *sockList) {
	memset(sockList, '\0', sizeof(SocketList));
	memset(&sockList->head, '\0', sizeof(SocketListHead));
	LIST_INIT(&(sockList->head));                      /* Initialize the list. */
	sockList->size = 0;
	sockList->initialized = 1;
	return sockList;
}

void UtilsLinkedList_addToListOfSockets(SocketList *sockList, int sockfd) {//add uniquely
	if( sockList->initialized != 1) {
		sockList = UtilsLinkedList_newListOfSockets(sockList);
	}

	SocketElement *pNewSockElem = (SocketElement *) malloc(sizeof(SocketElement));
	memset(pNewSockElem, '\0', sizeof(SocketElement));
	pNewSockElem->socketFd = sockfd;
	LIST_INSERT_HEAD(&sockList->head, pNewSockElem, socketElements);
	printf("Added socket %d to list\n", sockfd);

	sockList->size++;
	pNewSockElem = NULL;
}

void UtilsLinkedList_removeFromListOfSockets(SocketList *sockList, int sockfd) {
	SocketElement *pTempSockElem = NULL;
	int found = 0;
	//UtilsLinkedList_printListOfSockets(sockList);
	LIST_FOREACH(pTempSockElem, &sockList->head, socketElements ) {
		if( pTempSockElem->socketFd == sockfd ) {//this is the socket we want to remove
			printf("Removing socket %d from list\n", sockfd);
			LIST_REMOVE(pTempSockElem, socketElements);// Deletion.
			free(pTempSockElem);
			sockList->size--;
			found++;
		}
	}
	if( !LIST_EMPTY(&sockList->head) && found == 0 ) {
		printf("Socket %d not found\n", sockfd);
	}
}

void UtilsLinkedList_removeAllFromListOfSockets(SocketList *sockList) {
	SocketElement *pTempSockElem = NULL, *pNextSockElem = NULL;
	printf("Deleting List\n");
	if( LIST_EMPTY(&sockList->head) ) {
		printf("Attempt to delete empty list!\n");
	} else {
		pTempSockElem = LIST_FIRST(&sockList->head);                 /* Faster List Deletion. */
		while (pTempSockElem != NULL) {
			pNextSockElem = LIST_NEXT(pTempSockElem, socketElements);
			free(pTempSockElem);
			pTempSockElem = pNextSockElem;
			sockList->size--;
		}
		LIST_INIT(&sockList->head);
	}
}

void UtilsLinkedList_printListOfSockets(SocketList *sockList) {
	SocketElement *pTempSockElem = NULL;
	if( LIST_EMPTY(&sockList->head) ) {
		printf("List is empty!\n");
	} else {
		LIST_FOREACH(pTempSockElem, &sockList->head, socketElements ) {
			printf("Socket %d", pTempSockElem->socketFd);
			if(pTempSockElem->socketElements.le_next != NULL && pTempSockElem->socketElements.le_prev != NULL) {
				printf(" <-> ");
			} else if(pTempSockElem->socketElements.le_next != NULL ){
				printf(" -> ");
			} else  {
				printf(" -> END");
			}
		}
		printf("\n");
	}
}

