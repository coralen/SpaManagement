/********************************************/
/*   List.h                                 */
/*   a dynamic linked list with a header    */
/********************************************/


#ifndef _LIST_H
#define _LIST_H

#include "Def.h"
#include "General.h"

/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode, void (*freeFunc)(void*));					// erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*));		// return a pointer to the node

BOOL L_free(LIST* pList, void (*freeFunc)(void*));					// free list memory

int L_print(const LIST* pList, void(*print)(const void*));					// print the list content

int L_print_by_var(const LIST* pList, void(*print)(const void*, int), int var); // print the list content by an int variable

void L_func(const LIST* pList, void(*func)(const void*)); // general function on the list content

#endif