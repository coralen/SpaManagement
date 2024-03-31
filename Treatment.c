#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Treatment.h"
#include "List.h"

int initTreatmentNoCode(Treatment* pTreatment)
{
    getCorrectDate(&pTreatment->date);
    getCorrentHour(&pTreatment->date);
    getPrice(pTreatment);
    pTreatment->pTreatmentRoom = NULL;
    return 1;
}

void getTreatmentCode(char* code)
{
    char inputCode[MAX_STRING];
    do {
        printf("Enter treatment code, Format is T- following %d UPPER CASE letters\n", CODE);
        scanf(" %[^\n]", &inputCode);
    } while (!isCodeValid(inputCode, TREATMENT_START_CHAR));

    printf("\n");
    strcpy(code, inputCode);
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
    free(pTreatment->pTreatmentRoom);
}