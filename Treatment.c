#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Treatment.h"

int initTreatmentNoCode(Treatment* pTreatment)
{
    //duration? 
    getCorrectDate(&pTreatment->date);
    getCorrentHour(&pTreatment->date);
    getPrice(pTreatment);
    return 1;
}

void getTreatmentCode(char* code)
{
    char inCode[MAX_STRING];
    do {
        printf("Enter airport code  - %d UPPER CASE letters\n", CODE);
        scanf(" %[^\n]", &inCode);
    } while (!isCodeValid(inCode));

    printf("\n");
    strcpy(code, inCode);
}

int isCodeValid(const char* code)
{
    if (strlen(code) != CODE)
    {
        printf("code should be %d letters\n", CODE);
        return 0;
    }

    for (int i = 0; i < CODE; i++)
    {
        if (!isupper(code[i]))
        {
            printf("Need to be upper case letter\n");
            return 0;
        }
    }
    return 1;
}

void getPrice(Treatment* pTreatment)
{
    int price = 0;
    printf("Please enter the treatment price:\n");
    scanf("%d", &price);
    pTreatment->price = price;
}

void describeTreatment(Treatment* pTreatment)
{
    //implement in each treatment type
}

void freeTreatment(Treatment* pTreatment)
{
    //
}