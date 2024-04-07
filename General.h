#ifndef _GENERAL_H
#define _GENERAL_H

typedef enum { False, True , eNofBool} BOOL;
typedef enum { Available, Busy, eNofStatus } STATUS;

int				isCodeValid(const char* code, const char* firstChars);
void			generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*));
const char*		getBoolString(int boolNum);
const char*		getStatusString(int statusNum);

#endif