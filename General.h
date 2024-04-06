#ifndef _GENERAL_H
#define _GENERAL_H

typedef enum { False, True } BOOL;

int isCodeValid(const char* code, const char* firstChars);
void generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*));

#endif