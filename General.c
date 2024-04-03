#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Helper.h"
#include "General.h"

int isCodeValid(const char* code, const char* firstChars)
{

    if (strlen(code) != TOTAL_CODE)
    {
        printf("Code should be %s and %d digits\n", firstChars, CODE);
        return 0;
    }

    for (int i = TOTAL_CODE-CODE; i < TOTAL_CODE; i++)
    {
        if (!isdigit(code[i]))
        {
            printf("Need to be digits after the %s\n", firstChars);
            return 0;
        }
    }

    if (code[0] != firstChars[0] || code[1] != '-')
    {
        printf("The phrase must start with %s\n", firstChars);
        return 0;
    }
    return 1;
}