#include "../headers/Helper.h"

//Check beggining wirh R- (for rooms) or T- (for treatments)
int isCodeValid(const char* code, const char firstChar)
{
    if (strlen(code) != TOTAL_CODE)
    {
        printf("code should be %c- and %d letters\n", firstChar, CODE);
        return 0;
    }

    for (int i = TOTAL_CODE-CODE; i < TOTAL_CODE; i++)
    {
        if (!isupper(code[i]))
        {
            printf("Need to be upper case letter\n");
            return 0;
        }
    }
    return 1;
}

void generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*)) {
    void* ptr=array;

    for (int i = 0; i < elementsInArray; ++i) {
        generalFunction(ptr);
        ptr += sizeOfElement;
    }
}