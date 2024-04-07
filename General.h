#ifndef _GENERAL_H
#define _GENERAL_H

#define START 0
#define START_CHAR 'a'
#define END_CHAR 'z'

typedef enum { False, True , eNofBool} BOOL;
typedef enum { Available, Busy, eNofStatus } STATUS;

int				isCodeValid(const char* code, const char* firstChars);
void			generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*));
void			printBoolType();
void			capitalFirst(char* name);
const char*		getBoolString(const int boolNum);
const char*		getStatusString(const int statusNum);

#endif