#ifndef _GENERAL_H
#define _GENERAL_H

#include "Def.h"


//typedef enum {False, True} BOOL;

//int isCodeValid(const char* code, const char startChar);
void generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*));

#endif