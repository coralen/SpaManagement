/**************************************************************************/
/* def.h                                                                  */
/* This file contains GENERAL definitions used in several data structures */
/**************************************************************************/

#ifndef _DEF_H
#define _DEF_H

// a value not supposed in stack and queue
#define		EMPTY	0x7FFFFFFF

// new types
typedef void* DATA;					// a type for data (easy to change)

// Node
typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;

#endif