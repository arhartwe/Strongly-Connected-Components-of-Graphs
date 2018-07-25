/*
 * Name		: Andrew Hartwell
 * CruzID	: arhartwe
 * Assignment	: pa4
*/

//---------------------------------------------------------------
// List.c
// Implementation file for List ADT
//---------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs ------------------------------------------------------

// private Node type
typedef struct NodeObj
{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
}NodeObj;

// private NodeObj type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int length;
}ListObj;

List newList(void) // Creates a new list object
{
	List L;

	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	return(L);
}

void freeList(List* pL) // Frees the list
{
	if(pL != NULL && *pL != NULL)
	{	

		while(!isEmpty(*pL))
		{
			deleteFront(*pL);
		}

		free(*pL);
		pL = NULL;
	}
}

Node newNode(int data) // Creates a new list node
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node* N) // Frees a list node
{
	if(N != NULL && *N != NULL)
	{
		free(*N);
		*N = NULL;
	}
}

int isEmpty(List L) // Check if list is empty
{
	if(L == NULL)
	{
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	return(L->length == 0);
}

int length(List L) // Returns the number of elements in this list
{
	if(L == NULL)
	{
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

int index(List L) // If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1
{

	if(L == NULL)
	{
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	int i = 0;

	if(L->cursor != NULL)
	{

		Node temp = NULL;
		temp = L->front;
		while(temp != L->cursor)
		{
			i++;
			temp = temp->next;	
		}
		return i;
	}
	return -1;
}

int front(List L) // Returns front element
{
	if(L == NULL)
	{
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return L->front->data;
}

int back(List L) // Returns back element
{
	if(L == NULL)
	{
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return L->back->data;
}

int get(List L) // Returns cursor element
{
	if(L == NULL)
	{
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		printf("List Error: calling get() on an empty List\n");
		exit(1);
	}
	return L->cursor->data;
}

int equals(List A, List B) // Returns 1 if and only if List A and List B are the same integer
	// sequence. The states of the cursors in the two lists are not used
	// in determining equality
{
	Node aTemp = NULL;
	Node bTemp = NULL;

	if(A == NULL || B == NULL)
	{
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}

	aTemp = A->front;
	bTemp = B->front;

	while(aTemp != NULL && bTemp != NULL)
	{
		if(aTemp->data != bTemp->data)
		{
			return 0;
		}
		aTemp = aTemp->next;
		bTemp = bTemp->next;
	}
	return (aTemp == NULL && bTemp == NULL);
}

void clear(List L) // Resets list L to its original empty state
{

	if(isEmpty(L))
	{

		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->length = 0;

	}
	else
	{
		while(L->front->next != NULL)
		{
			deleteFront(L);
		}
		Node N = L->front;
		freeNode(&N);
		N = NULL;
		L->length--;
	}


}

void moveFront(List L) // If list is non-empty, places the cursor under the front element,
	// otherwise does nothing
{
	if(length(L) > 0)
	{
		L->cursor = L->front;
	}
}

void moveBack(List L) // If list is non-empty, places the cursor under the back element,
	// otherwise does nothing
{
	if(length(L) > 0)
	{
		L->cursor = L->back;
	}
}

void movePrev(List L) // If cursor is defined and not at front, moves cursor one  step toward
	// front of this list, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined, does nothing
{
	if(L->cursor != NULL && L->cursor != L->front)
	{
		L->cursor = L->cursor->prev;
	}
	else if(L->cursor != NULL && L->cursor == L->front)
	{
		L->cursor = NULL;
	}
	else
	{
		return;
	}
}

void moveNext(List L) // If cursor is defined and not at back, moves cursor one step toward
	// back of the list, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing
{
	if(L->cursor != NULL && L->cursor != L->back)
	{
		L->cursor = L->cursor->next;
	}
	else if(L->cursor != NULL && L->cursor == L->back)
	{
		L->cursor = NULL;
	}
	else
	{
		return;		
	}
}

void prepend(List L, int data) // Insert new element into this list. If list is non-empty,
	// insertion takes place before front element
{
	Node N = newNode(data);
	Node temp  = NULL;
	if(L == NULL)
	{
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		L->front = L->back = N;
	}
	else
	{
		temp = L->front;
		L->front->prev = N;
		L->front = N;
		L->front->next = temp;
	}
	L->length++; 
}

void append(List L, int data) // Insert new element into this list. If list is non-empty,
	// insertion takes place after back element.
{
	Node N = newNode(data);
	Node temp = NULL;
	if(L == NULL)
	{
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		L->front = L->back = N;
	}
	else
	{
		temp = L->back;
		L->back->next = N;
		L->back->next->prev = temp;
		L->back = N;	
	}
	L->length++;
}


void insertBefore(List L, int data) // Insert new element before cursor
{
	Node N = newNode(data);

	if(L->cursor == L->front)
	{
		L->front = N;
		L->cursor->prev = N;
		N->prev = NULL;
		N->next = L->cursor;
	}
	else
	{

		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev = N;

	}
	L->length++;
}

void insertAfter(List L, int data) // Insert new element after cursor
{
	Node N = newNode(data);
	if(L->cursor->next == NULL)
	{
		L->back = N;
		L->cursor->next = N;
		N->next = NULL;
		N->prev = L->cursor;
	}
	else
	{
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
	}
	L->length++;
}

void deleteFront(List L) // Deletes the front element
{

	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	N = L->front;
	if(L->cursor == L->front)
	{	
		L->cursor = NULL;
	}

	if(length(L) > 2)
	{
		L->front = L->front->next;
		L->front->prev = NULL;

	}
	else if(length(L) == 2)
	{
		L->front = L->front->next;
		L->front->prev = NULL;
		L->front->next = NULL;
	}

	else
	{
		L->front = NULL;
		L->back = NULL;
	}

	L->length--;
	freeNode(&N);

}

void deleteBack(List L) // Deletes the back element
{
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L))
	{
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor == L->back)
	{
		L->cursor = NULL;
	}
	N = L->back;
	if(length(L) > 2)
	{
		L->back = L->back->prev;
		L->back->next = NULL;
	}
	else if(length(L) == 2)
	{
		L->back = L->back->prev;
		L->back->next = NULL;
		L->back->prev = NULL;
	}
	else
	{
		L->front = NULL;
		L->back = NULL;
	}        
	L->length--;
	freeNode(&N);
}

void delete(List L) // Deletes cursor element, making cursor undefined
{

	if(length(L) > 0 && index(L) >= 0)
	{
		Node N = NULL;
		N = L->cursor;
		if(L->cursor == L->front)
		{
			L->front = L->cursor->next;
			L->cursor = NULL;
		}
		else if(L->cursor == L->back)
		{
			L->back = L->cursor->prev;
			L->back->next = NULL;
			L->cursor = NULL;
		}
		else
		{
			L->cursor->prev->next = L->cursor->next;
			L->cursor->next->prev = L->cursor->prev;
			L->cursor = NULL;
		}
		L->length--;
		freeNode(&N);
	}


}

void printList(FILE* out, List L) // Prints the values in the list
{
	Node N = NULL;

	if(L == NULL)
	{
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}

	for(N = L->front; N != NULL; N = N->next)
	{
		fprintf(out, "%d ", N->data);
	}
	fprintf(out,"\n");
}

List copyList(List L) // Returns a new list representing the same integer sequence as this
	// list. The cursor in the new list is undefined, regardless of the state of the
	// cursor in the list. This list is unchanged.
{

	//Node N = NULL;
	List new = newList();
	if(index(L) == -1)
	{	
		return new;
	}
	else
	{
		moveFront(L);
		while(L->cursor->data != L->back->data)
		{
			int newInt = L->cursor->data;
			append(new, newInt);
			moveNext(L);
		}
		int back = L->back->data;
		append(new, back);
		moveFront(L);
		return new;
	}
}

