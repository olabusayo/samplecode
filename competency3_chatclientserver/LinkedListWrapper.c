/*
 * LinkedListWrapper.c
 *
 *  Created on: May 3, 2017
 *      Author: root
 */
#include "UtilsLinkedList.h"

int main() {

	int i = 0;

	//SocketElement *e1_p, *e2_p, *next_p = { ((void *)0) };
	SocketList mySockList = {0};

	UtilsLinkedList_newListOfSockets(&mySockList);

	for( i = 1; i <= 10; i++ ) {
		UtilsLinkedList_addToListOfSockets(&mySockList, i);
	}

	for( i = 10; i > 0; i--) {
		UtilsLinkedList_removeFromListOfSockets(&mySockList, i);
	}

	UtilsLinkedList_printListOfSockets(&mySockList);
	UtilsLinkedList_removeFromListOfSockets(&mySockList, 5);
	UtilsLinkedList_printListOfSockets(&mySockList);
	UtilsLinkedList_removeFromListOfSockets(&mySockList, 7);
	UtilsLinkedList_printListOfSockets(&mySockList);

	UtilsLinkedList_addToListOfSockets(&mySockList, 6);
	UtilsLinkedList_printListOfSockets(&mySockList);
	UtilsLinkedList_addToListOfSockets(&mySockList, 5);
	UtilsLinkedList_printListOfSockets(&mySockList);
	UtilsLinkedList_addToListOfSockets(&mySockList, 6);
	UtilsLinkedList_printListOfSockets(&mySockList);

	UtilsLinkedList_removeFromListOfSockets(&mySockList, 6);
	UtilsLinkedList_printListOfSockets(&mySockList);


	UtilsLinkedList_removeAllFromListOfSockets(&mySockList);
	UtilsLinkedList_printListOfSockets(&mySockList);

	//	SocketListHead head = SLIST_HEAD_INITIALIZER(head);
	//	//SocketListHead *headp;                /* Singly-linked List head. */
	//	SLIST_INIT(&head);                      /* Initialize the list. */
	//
	//	e1_p = (SocketElement *) malloc(sizeof(SocketElement));      /* Insert at the head. */
	//	e1_p->fD = 1;
	//	SLIST_INSERT_HEAD(&head, e1_p, socketElements);
	//
	//	e2_p = (SocketElement *) malloc(sizeof(SocketElement));      /* Insert after. */
	//	e2_p->fD = 2;
	//	SLIST_INSERT_AFTER(e1_p, e2_p, socketElements);
	//
	//	/*SLIST_REMOVE(&head, e2_p, socketElement, socketElements);// Deletion.
	//	free(e2_p);
	//
	//	e3_p = SLIST_FIRST(&head);
	//	SLIST_REMOVE_HEAD(&head, socketElements);      // Deletion from the head.
	//	free(e3_p);*/
	//
	//	// Forward traversal.
	//	printf("At traversal\n");
	//	SLIST_FOREACH(next_p, &head, socketElements) {
	//		i++;
	//		printf("i: %d\n", i);
	//		printf("element %d: %d\n", i, next_p->fD);
	//	}

	printf("Exiting program");

//	//List example
//	LIST_HEAD(listhead, entry) head =
//			LIST_HEAD_INITIALIZER(head);
//	struct listhead *headp;                 /* List head. */
//	struct entry {
//		LIST_ENTRY(entry) entries;      /* List. */
//	} *n1, *n2, *n3, *np, *np_temp;
//
//	LIST_INIT(&head);                       /* Initialize the list. */
//
//	n1 = malloc(sizeof(struct entry));      /* Insert at the head. */
//	LIST_INSERT_HEAD(&head, n1, entries);
//
//	n2 = malloc(sizeof(struct entry));      /* Insert after. */
//	LIST_INSERT_AFTER(n1, n2, entries);
//
//	n3 = malloc(sizeof(struct entry));      /* Insert before. */
//	LIST_INSERT_BEFORE(n2, n3, entries);
//
//	LIST_REMOVE(n2, entries);               /* Deletion. */
//	free(n2);
//	/* Forward traversal. */
////	LIST_FOREACH(np, &head, entries)
////	np-> ...
//
//	while (!LIST_EMPTY(&head)) {            /* List Deletion. */
//		n1 = LIST_FIRST(&head);
//		LIST_REMOVE(n1, entries);
//		free(n1);
//	}
//
//	n1 = LIST_FIRST(&head);                 /* Faster List Deletion. */
//	while (n1 != NULL) {
//		n2 = LIST_NEXT(n1, entries);
//		free(n1);
//		n1 = n2;
//	}
//	LIST_INIT(&head);


	return 0;
}




