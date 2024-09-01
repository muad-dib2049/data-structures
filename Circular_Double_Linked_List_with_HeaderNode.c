#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_INVALID_POSITION 2
#define EXIT_INSUFFICIENT_MEMORY 3

/* 	Defines the structure of a NODE.
	Since there is a previous and next pointer to node, the list is doubly linked.
	The first node of the list is the head node.
	The previous pointer of the first node of the list (head node), points to the last element of the list.
	Therefore, it is a circular list.
	The next pointer of the head node points to the first element of the list, and the previous points to the last.
	This facilitates the implementation of the the insert and delete a node by index methods.
*/

typedef struct node {
	int data;
	struct node * previous;
	struct node * next;
}NODE;

/* Creates a new data type LIST set as a pointer to node */
typedef NODE * LIST_DOUBLE_LINKED_CIRCULAR_HEAD;

void createList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *);
int isListEmpty(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);
int listSize(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);
void insertNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *, int, int);
int searchNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD, int);
void deleteNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *, int);
void destroyList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *);

void insertNodeFirst(LIST_DOUBLE_LINKED_CIRCULAR_HEAD, int);
void insertNodeLast(LIST_DOUBLE_LINKED_CIRCULAR_HEAD, int);
int deleteNodeFirst(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);
int deleteNodeLast(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);
void swapEnds(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);

void displayList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD);


/* MAIN FUNCTION */
int main(void) {
	LIST_DOUBLE_LINKED_CIRCULAR_HEAD list;

	createList(&list);

	insertNode(&list, 77, 1);
	printf("\n\nlist[1]: %d", searchNode(list, 1));

	deleteNode(&list, 1);

	insertNode(&list, 88, 1);
	insertNode(&list, 66, 1);
	insertNode(&list, 55, 3);
	insertNode(&list, 44, 2);
	insertNode(&list, 33, 5);
	insertNodeFirst(list, 22);
	insertNodeFirst(list, 11);
	insertNodeLast(list, 01);
	insertNodeLast(list, 2);
	insertNodeFirst(list, 9);

	printf("\n\nIs List empty? %s", isListEmpty(list)?"YES":"NO");
	printf("\nList size: %d\n", listSize(list));

	displayList(list);

	printf("\nElement %d was deleted from first position of the list.", deleteNodeFirst(list));
	printf("\nElement %d was deleted from first position of the list.", deleteNodeFirst(list));

	printf("\n\nElement %d was deleted from last position of the list.", deleteNodeLast(list));
	printf("\nElement %d was deleted from last position of the list.", deleteNodeLast(list));

	displayList(list);

	swapEnds(list);
	displayList(list);

	destroyList(&list);
	printf("\n");
	return EXIT_SUCCESS;
}


/* Function to initialize the list and allocate memory for the head node */
void createList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *p) {
	*p = (NODE *) malloc(sizeof(NODE));

	if (*p == NULL) {
		printf("\n\n<< ERROR! Insufficient memory to create the head node! >>\n\n");
		exit(EXIT_INSUFFICIENT_MEMORY);
	}

	(*p)->data = 0;
	(*p)->previous = *p;
	(*p)->next = *p;

	printf("LIST CREATED WITH SUCCESS!\n");
	printf("\nIs List empty? %s", isListEmpty(*p)?"YES":"NO");
	printf("\nList size: %d\n", listSize(*p));
}

/* Function to tell if the list is empty or not */
int isListEmpty(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
	if (l == NULL) {
		return 1;
	}

	return (l->data == 0);
}

/* Function to get the size of the list */
int listSize(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
	if (isListEmpty(l) == 1) {
		return 0;
	} else {
		return (l->data);
	}
}

/* Function to insert/create a new node in the list based on index */
void insertNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *p, int data, int index) {
	int sizeOfList = listSize(*p);

	if (index < 1 || index > (sizeOfList + 1)) {
		printf("\n\n<< ERROR! Invalid insert index: Element out of bound! >>\n\n");
		exit(EXIT_INVALID_POSITION);
	}

	NODE * newNode = NULL;
	NODE * temp = NULL;

	newNode = (NODE *) malloc(sizeof(NODE));

	if (newNode == NULL) {
		printf("\n\n<< ERROR! Insufficient memory to create a new node! >>\n\n");
		exit(EXIT_INSUFFICIENT_MEMORY);
	}

	newNode->data = data;
	temp = *p;

	for (int i = index; i > 1; i--) {
		temp = temp->next;
	}

	newNode->previous = temp;
	newNode->next = temp->next;
	temp->next = newNode;
	newNode->next->previous = newNode;

	(*p)->data = sizeOfList + 1;

	printf("\n\nINSERT: Node %d inserted in the index %d of the list.", data, index);
}

/* Function to retrieve the data of a node by index */
int searchNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l, int index) {
	if (index < 1 || index > listSize(l)) {
		printf("\n\n<< ERROR! Invalid search index: Element out of bound! >>\n\n");
		exit(EXIT_INVALID_POSITION);
	}

	for (; index > 0; index--) {
		l = l->next;
	}
	return (l->data);
}

/* Function to delete a node from the list by index */
void deleteNode(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *p, int index) {
	NODE * temp = NULL;
	int sizeOfList = listSize(*p);
	int removedDataValue = 0;

	if (index < 1 || index > sizeOfList) {
		printf("\n\n<< ERROR! Invalid delete index: Element out of bound! >>\n\n");
		exit(EXIT_INVALID_POSITION);
	}


	for (temp = (*p)->next; index > 1; index--) {
		temp = temp->next;
	}

	temp->previous->next = temp->next;
	temp->next->previous = temp->previous;

	removedDataValue = temp->data;

	free(temp);
	temp = NULL;

	(*p)->data = sizeOfList - 1;

	printf("\n\nDELETE: Node %d removed from index %d of the list", removedDataValue, index);
}

/* Function to remove/deletes all nodes of the list - destroys the full list */
void destroyList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD *p) {
	if (*p != NULL) {
        NODE * temp = (*p)->next;

        printf("\n*** Destroying list... ***\n");

        do {
            *p = temp->next;
            free(temp);
            temp = *p;
        } while (temp != *p && temp != NULL);

        temp = NULL;
        *p = NULL;

        printf("\nIs List empty? %s", isListEmpty(*p)?"YES":"NO");
        printf("\nList size: %d", listSize(*p));

        printf("\n\n*** List destroyed successfully! ***\n");
	}
}

/* Function to insert/create a new node in the beginning of the list */
void insertNodeFirst(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l, int data) {
    NODE * novo = NULL;

    novo = (NODE *) malloc(sizeof(NODE));
    if (novo == NULL) {
		printf("\n\n<< ERROR! Insufficient memory to create a new node! >>\n\n");
		exit(EXIT_INSUFFICIENT_MEMORY);
	}
	novo->data = data;
	novo->previous = l;
	novo->next = l->next;
	l->next->previous = novo;
	l->next = novo;
	l->data = listSize(l) + 1;
}

/* Function to insert/create a new node in the end of the list */
void insertNodeLast(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l, int data) {
    NODE * novo = NULL;

    novo = (NODE *) malloc(sizeof(NODE));
    if (novo == NULL) {
		printf("\n\n<< ERROR! Insufficient memory to create a new node! >>\n\n");
		exit(EXIT_INSUFFICIENT_MEMORY);
	}
    novo->data = data;
    novo->previous = l->previous;
    novo->next = l;
    l->previous->next = novo;
    l->previous = novo;
    l->data = listSize(l) + 1;
}

/* Function to delete the first node of the list - Not the head node, the first element pointed by the head node */
int deleteNodeFirst(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
    NODE * temp = NULL;
    int sizeOfList = listSize(l);
    int removedDataValue = 0;

    if (sizeOfList > 0) {
        temp = l->next;
        l->next = temp->next;
        l->next->previous = l;

        removedDataValue = temp->data;

        free(temp);
        temp = NULL;

        l->data = sizeOfList - 1;

        return removedDataValue;
    } else {
        printf("\n\n<< ERROR! Delete index out of bound: first node not found! >>\n\n");
		exit(EXIT_FAILURE);
    }
}

/* Function to delete the last node of the list */
int deleteNodeLast(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
    NODE * temp = NULL;
    int sizeOfList = listSize(l);
    int removedDataValue = 0;

    if (sizeOfList > 0) {
        temp = l->previous;
        l->previous = temp->previous;
        l->previous->next = l;

        removedDataValue = temp->data;

        free(temp);
        temp = NULL;

        l->data = sizeOfList - 1;

        return removedDataValue;
    } else {
        printf("\n\n<< ERROR! Delete index out of bound: last node not found! >>\n\n");
		exit(EXIT_FAILURE);
    }
}

/* Changes the place of the first and last element of the list - First becomes the last, last becomes the first */
void swapEnds(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
    if (listSize(l) > 0) {
        int first, last;

        first = deleteNodeFirst(l);
        last  = deleteNodeLast(l);

        insertNodeFirst(l, last);
        insertNodeLast(l, first);

        printf("\n\nFirst and last node swapped positions!\n");
    }
}

/* Prints in the screen the data of all nodes of the list - Doesnt print the head node */
void displayList(LIST_DOUBLE_LINKED_CIRCULAR_HEAD l) {
    NODE * temp = l->next;
    int sizeOfList = listSize(l);

    printf("\n\n----- Printing list! -----\n");

    for (int i = 1; i <= sizeOfList; i++) {
        printf("\nlist[%d]= %d", i, temp->data);
        temp = temp->next;
    }
    printf("\n\n----- List printed successfully! -----\n");
}
