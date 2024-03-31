#include "Helper.h"


int isCodeValid(const char* code, const char* firstChar)
{
    if (strlen(code) != TOTAL_CODE)
    {
        printf("code should be %s and %d letters\n", firstChar, CODE);
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

    if (code[0] != firstChar || code[1] != '-')
    {
        printf("The phrase must start with %s\n", firstChar);
        return 0;
    }
    return 1;
}