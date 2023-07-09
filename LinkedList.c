#define _CRT_SECURE_NO_WARNINGS
#include "LinkedList.h"
#define SIZE_ 40

void PrintList(LinkedList* head)
{//	Print the whole list elements
	LinkedList* temp = head;
	while (temp != NULL)
	{
		//	Print every element on the list
		printf("   %s\n", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

LinkedList * BuildNode(char* str)
{//	Creat list with 1 organ and returns a pointer
	LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));	//	Allocate list memory
	node->data = (char*)malloc(SIZE_+1);	//	Allocate string memory
	strcpy(node->data, str);	//	fill data field
	node->next = NULL;
	return node;
}

LinkedList* addToStart(LinkedList* head, char* str)
{//	Create a new element and make him the head of the list.
	LinkedList* new_elem = BuildNode(str);
	new_elem->next = head;
	return new_elem;
}

LinkedList * FreeList(LinkedList* head)
{//	Free allocated memory of the list
	LinkedList *temp;
	while (head != NULL)
	{	//	Free every element
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}

LinkedList* DeleteElement(LinkedList* head, char* str)
{//	Delete one element fromt the list
	LinkedList *previous = head, *current = head->next;
	if (head == NULL)	//	Emptey list case
		return head;
	if (strcmp(head->data,str)==0)	
	{//	If the head of the list is the value
		LinkedList *temp = head;
		head = head->next;
		free(temp);
		return head;
	}
	while (previous != NULL)	//	Find the specific element in the list
	{
		if (strcmp(previous->data, str) == 0)
			break;
		current = previous;
		previous = previous->next;
	}
	if (previous != NULL)
		current->next = previous->next;
	free(previous);	//	Free element
	return head;
}

int isInList(LinkedList* head, char* str)
{//	Check if the specific element is in the list
	LinkedList* temp = head;
	while (temp != NULL)
	{
		if (strcmp(temp->data, str) == 0)
			//	If found him
			return 1;
		temp = temp->next;
	}
	return 0;
}

LinkedList * delete_doubles(LinkedList* head)
{//	Make sure every element appear only once
	if (head == NULL)
		return head;
	LinkedList* temp = head,*t;
	while (temp->next != NULL)
	{
		if (isInList(temp->next, temp->data))
		{
			//	Save the the next node location and than delete
			t = temp->next; 
			head = DeleteElement(head, temp->data);
			temp = t;
		}
		else
			temp = temp->next;
	}
	return head;
}

LinkedList* link_lists(LinkedList* curr, LinkedList* new)
{//	Link tho lists into one
	LinkedList* temp = curr;
	//	If one list is NULL
	if (curr == NULL)
		return new;
	if (new == NULL)
		return curr;
	//	Connect between those two
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return curr;
}
