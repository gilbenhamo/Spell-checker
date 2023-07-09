#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//	Linked list struct definition
typedef struct LinkedList LinkedList;
struct LinkedList {
	char* data;
	LinkedList  * next;
};

//	Mission functions
void	PrintList(LinkedList*);						//	Print the whole list
LinkedList *	BuildNode(char*);					//	Creat list with 1 organ and returns a pointere
LinkedList *	addToStart(LinkedList *, char*);	//	Create a new element and make him the head of the list.
LinkedList *	FreeList(LinkedList *);				//	Free allocated memory
LinkedList *	DeleteElement(LinkedList *, char*);	//	Delete specific element from the list
int isInList(LinkedList*, char*);					//	Check if the element is in list

//	Help Functions
LinkedList *	link_lists(LinkedList*, LinkedList*);	//	Link tho lists into one
LinkedList *	delete_doubles(LinkedList*);			//	Make sure every element appear only once
