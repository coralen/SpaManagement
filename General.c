#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../headers/Helper.h"
#include "../headers/General.h"

const char* boolString[eNofBool] = { "False", "True"};
const char* statusString[eNofStatus] = { "Available", "Busy" };

int isCodeValid(const char* code, const char* firstChars)
{

    if (strlen(code) != TOTAL_CODE)
    {
        printf("Code should be %s and %d digits\n", firstChars, CODE);
        return 0;
    }

    for (int i = TOTAL_CODE - CODE; i < TOTAL_CODE; i++)
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

void generalArrayFunction(void* array, int elementsInArray, int sizeOfElement, void (generalFunction)(void*))
{
    char* ptr = (char*)array;

    for (int i = 0; i < elementsInArray; ++i) 
    {
        generalFunction(ptr);
        ptr += sizeOfElement;
    }
}

const char* getBoolString(const int boolNum)
{
    return boolString[boolNum];
}

const char* getStatusString(const int statusNum)
{
    return statusString[statusNum];
}

void printBoolType()
{
    for (int i = 0; i < eNofBool; i++)
        printf("%d - %s\n", i, getBoolString(i));
}

void capitalFirst(char* name)
{
    if (name[START] >= START_CHAR && name[START] <= END_CHAR) name[START] = toupper(name[START]);
    for (int i = 1; i < strlen(name); i++)
        if (name[i] >= START_CHAR && name[i] <= END_CHAR && name[i - 1] == ' ') name[i] = toupper(name[i]);
}