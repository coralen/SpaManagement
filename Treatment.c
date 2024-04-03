#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Treatment.h"
#include "General.h"

static const char* treatmentTypeString[TREATMENT_TYPE_COUNT] = { "Massage", "Hot Stones" ,"Meni Pedi" };
static const int treatmentDurationInt[TREATMENT_TYPE_COUNT] = { 45, 30 , 60 };
static const int treatmentPriceInt[TREATMENT_TYPE_COUNT] = { 300, 250, 100 };

int initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, RoomType rType)
{
    //getCorrectDate(&pTreatment->date);
    //getCorrentHour(&pTreatment->date);
    pTreatment->duration = getTreatmentDurationInt(option);
    pTreatment->price = getTreatmentPriceInt(option);
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
        printf("Enter treatment code, Format is T- following %d digits\n", CODE);
        scanf(" %[^\n]", inputCode);
    } while (!isCodeValid(inputCode, TREATMENT_START_CHARS));

    strcpy(code, inputCode);
}

int initMassage(Treatment* pTreatment, Room* pRoom, RoomType rType)
{
    getMassageType(&pTreatment->data.massage);
    if (!getNotesFromClient(&pTreatment->data.massage)) return 0;
    return 1;
}

void initHotStones(Treatment* pTreatment, Room* pRoom, RoomType rType)
{
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

void freeTreatmentWrapper(void* treatment) 
{
    freeTreatment((Treatment*)treatment);
}

void printTreatmentTypes()
{
    for (int i = 0; i < TREATMENT_TYPE_COUNT; i++)
        printf("%d - %s\n", i, getTreatmentTypeString(i));
}

const char* getTreatmentTypeString(int typeNum)
{
    return treatmentTypeString[typeNum];
}

const int getTreatmentDurationInt(int typeNum)
{
    return treatmentDurationInt[typeNum];
}

const int getTreatmentPriceInt(int typeNum)
{
    return treatmentPriceInt[typeNum];
}

void printTreatment(const Treatment* pTreatment)
{
    printf("%-10s\t%-10s\t%-10d\t%-10d\t%-10s", pTreatment->code, getMassageTypeString(pTreatment->type), pTreatment->duration, pTreatment->price, pTreatment->pTreatmentRoom->code);
    if (!pTreatment->date.day) printf("None\t");
    else printDate(&pTreatment->date);
    printf("\n");
}

void printTreatmentHeaders()
{
    printf("Code%-10s\tType%-10s\tDuration%-15s\tPrice%-15s\tRoom%-10s\tDate%-10s\t", " ", " ", " ", " ", " ", " ");
    printf("\n");
}