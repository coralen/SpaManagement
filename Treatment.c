#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Treatment.h"
#include "List.h"

int initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, RoomType rType)
{
    getCorrectDate(&pTreatment->date);
    getCorrentHour(&pTreatment->date);
    pTreatment->duration = treatmentDurationInt[option];
    pTreatment->price = treatmentPriceInt[option];
    pTreatment->type = (TreatmentType)option;
    pTreatment->pTreatmentRoom = pRoom;

    switch (option)
    {
    case 1:
        if (!initMassage(pTreatment, pRoom, rType)) return 0;
        break;

    case 2:
        initHotStones(pTreatment, pRoom, rType);
        break;

    case 3:
        initMeniPedi(pTreatment, pRoom, rType);
        break;
    }

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

int initMassage(Treatment* pTreatment, Room* pRoom, RoomType rType)
{
    getMassageType(&pTreatment->data.massage);
    if (!getNotesFromClient(&pTreatment->data.massage)) return 0;
}

void initHotStones(Treatment* pTreatment, Room* pRoom, RoomType rType)
{
    // implement
    getHotStonesType(&pTreatment->data.hotStones);
    getStonesPlacement(&pTreatment->data.hotStones);
}

/* Talya -  implement init meni pedi */
void initMeniPedi(Treatment* pTreatment, Room* pRoom, RoomType rType)
{}


void describeTreatment(Treatment* pTreatment)
{
    //implement in each treatment type
}

void freeTreatment(Treatment* pTreatment)
{
    free(pTreatment);
}

void printTreatmentTypes()
{
    for (int i = 0; i < TREATMENT_TYPE_COUNT; i++)
        printf("%d - %s\n", i, treatmentTypeString[i]);
}
