/*
 * LinkedListWrapper.c
 *
 *  Created on: May 3, 2017
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

int main() {

	int i = 0;

	struct sListElement {
		int fD;
		SLIST_ENTRY(sListElement) sListElements;     /* Singly-linked List. */
	} *e1_p, *e2_p, *e3_p, *next_p;
	SLIST_HEAD(sListHead, sListElement) head = SLIST_HEAD_INITIALIZER(head);
	struct sListHead *headp = &head;                /* Singly-linked List head. */

	SLIST_INIT(headp);                      /* Initialize the list. */

	e1_p = malloc(sizeof(struct sListElement));      /* Insert at the head. */
	e1_p->fD = 1;
	SLIST_INSERT_HEAD(headp, e1_p, sListElements);

	e2_p = malloc(sizeof(struct sListElement));      /* Insert after. */
	e2_p->fD = 2;
	SLIST_INSERT_AFTER(e1_p, e2_p, sListElements);

	SLIST_REMOVE(headp, e2_p, sListElement, sListElements);/* Deletion. */
	free(e2_p);

	e3_p = SLIST_FIRST(headp);
	SLIST_REMOVE_HEAD(headp, sListElements);      /* Deletion from the head. */
	free(e3_p);

	/*0 Forward traversal. */

	SLIST_FOREACH(next_p, headp, sListElements) {
		i++;
		printf("element %d: %d\n", i, next_p->fD);
	}
	//
	//     while (!SLIST_EMPTY(headp)) {           /* List Deletion. */
	//             n1 = SLIST_FIRST(headp);
	//             SLIST_REMOVE_HEAD(headp, entries);
	//             free(n1);
	//     }
	return 0;
}
