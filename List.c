/**************/
/*   List.c   */
/**************/


#include <stdio.h>
#include <stdlib.h>
#include "List.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
    if (pList == NULL)
        return False;	// no list to initialize

    pList->head.next = NULL;
    return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value)
{
    NODE* tmp;

    if (!pNode)
        return NULL;

    tmp = (NODE*)malloc(sizeof(NODE));	// new node

    if (tmp != NULL) {
        tmp->key = Value;
        tmp->next = pNode->next;
        pNode->next = tmp;
    }
    return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, void (*freeFunc)(void*))
{
    NODE* tmp = pNode;
    if (!pNode || !(tmp = pNode->next))
        return False;

    pNode->next = tmp->next;
    if (freeFunc != NULL)
        freeFunc(tmp->key);
    free(tmp);
    return True;
}

BOOL L_delete_current(NODE* pHead, NODE* target, void (*freeFunc)(void*))
{
    if (!pHead || !target) return False;

    NODE* current = pHead;
    NODE* previous = NULL;

    while (current != NULL && current != target) {
        previous = current;
        current = current->next;
    }

    if (current != target) return False;
    if (previous == NULL) 
        pHead = current->next;
    else 
        previous->next = current->next;

    if (freeFunc != NULL) freeFunc(current->key);
    free(current);

    return True;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*))
{
    const NODE* temp = NULL;
    if (!pNode) return NULL;
    while (pNode != NULL)
    {
        if (compare(pNode->key, Value) == 0)
        {
            temp = pNode;
            break;
        }
        pNode = pNode->next;
    }

    return temp;
}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList, void (*freeFunc)(void*))
{
    NODE* tmp;

    if (!pList) return False;

    tmp = &(pList->head);
    BOOL res = True;

    while (res)
    {
        res = L_delete(tmp, freeFunc);
    }

    return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST* pList, void(*print)(const void*))
{

    NODE* tmp;
    int		c = 0;

    if (!pList)
        return False;

    printf("\n");

    for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
        print(tmp->key);

    printf("\n");
    return c;
}


int L_print_by_var(const LIST* pList, void(*print)(const void*, int), int var)
{

    NODE* tmp;
    int	funcVar = var, c = 0;

    if (!pList)
        return False;

    printf("\n");

    for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
        print(tmp->key, funcVar);

    printf("\n");
    return c;
}

void L_func(const LIST* pList, void(*func)(const void*))
{

    NODE* tmp;

    if (!pList)
        return;

    for (tmp = pList->head.next; tmp; tmp = tmp->next)
        func(tmp->key);

}