#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Treatment.h"
#include "General.h"
#include "Helper.h"

static const char* treatmentTypeString[eNofTreatmentType] = { "Massage", "Hot Stones" ,"Meni Pedi" };
static const int treatmentDurationInt[eNofTreatmentType] = { 45, 30 , 60 };
static const int treatmentPriceInt[eNofTreatmentType] = { 300, 250, 100 };

int initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, Employee* pEmployee, Date *pDate)
{
    pTreatment->date = *pDate;
    pTreatment->duration = getTreatmentDurationInt(option);
    pTreatment->price = getTreatmentPriceInt(option);
    pTreatment->isActive = 0;
    pTreatment->type = (TreatmentType)option;
    pTreatment->pTreatmentRoom = pRoom;
    pTreatment->pTreatmentEmployee = pEmployee;

    switch (option)
    {
    case eMassage:
        if (!initMassage(pTreatment)) return 0;
        break;

    case eHotStones:
        initHotStones(pTreatment);
        break;

    case eMeniPedi:
        initMenicurePedicure(pTreatment);
        break;
    }

    return 1;
}

void getTreatmentCode(char* code)
{
    char inputCode[MAX_STRING + 1];

    do {
        printf("Enter treatment code, Format is T- following %d digits\n", CODE);
        scanf(SCANF_FORMAT, inputCode);
        while (getchar() != '\n');
    } while (!isCodeValid(inputCode, TREATMENT_START_CHARS));

    strcpy(code, inputCode);
}

int initMassage(Treatment* pTreatment)
{
    getMassageType(&pTreatment->data.massage.type);
    if (!getNotesFromClient(&pTreatment->data.massage.notesFromClient)) return 0;
    return 1;
}

void initHotStones(Treatment* pTreatment)
{
    getHotStonesType(&pTreatment->data.hotStones);
    getStonesPlacement(&pTreatment->data.hotStones);
}

int initMenicurePedicure(Treatment* pTreatment)
{
    setMedicoreAndPedicore(&pTreatment->data.meniPedi);
    if (!setPolishColor(&pTreatment->data.meniPedi.color)) return 0;
    setNailArtType(&pTreatment->data.meniPedi);
    return 1;
}

void describeTreatment(Treatment* pTreatment)
{
    //implement in each treatment type
}

void printTreatmentTypes()
{
    for (int i = 0; i < eNofTreatmentType; i++)
        printf("%d - %s\n", i, getTreatmentTypeString(i));
}

const char* getTreatmentTypeString(const int typeNum)
{
    return treatmentTypeString[typeNum];
}

const int getTreatmentDurationInt(const int typeNum)
{
    return treatmentDurationInt[typeNum];
}

const int getTreatmentPriceInt(int typeNum)
{
    return treatmentPriceInt[typeNum];
}

void printTreatment(const Treatment* pTreatment)
{
    printf("%-5s\t%-10s\t%-10s\t%-10d\t%-5d\t%-5s\t%-10d\t", pTreatment->code, getTreatmentTypeString(pTreatment->type), getBoolString(pTreatment->isActive), pTreatment->duration, pTreatment->price, pTreatment->pTreatmentRoom->code, pTreatment->pTreatmentEmployee->id);
    if (!pTreatment->date.day) printf("%-10s\t", "None");
    else printDate(&pTreatment->date);
    printf("%-10d\t", pTreatment->date.hour);
    printf("\n");
}

void printTreatmentWithData(const Treatment* pTreatment, int type)
{
    if (pTreatment->type != type) return;
    printf("%-5s\t%-10s\t%-10s\t%-10d\t%-5d\t%-5s\t%-10d\t", pTreatment->code, getTreatmentTypeString(pTreatment->type), getBoolString(pTreatment->isActive) ,pTreatment->duration, pTreatment->price, pTreatment->pTreatmentRoom->code, pTreatment->pTreatmentEmployee->id);
    if (!pTreatment->date.day) printf("%-10s\t", "None");
    else printDate(&pTreatment->date);
    printf("%-10d\t", pTreatment->date.hour);
    MASSAGE_TYPE_SWITCH_CASE(pTreatment->type, printMassage, &pTreatment->data.massage, printHotStones, &pTreatment->data.hotStones, printMenicurePedicure, &pTreatment->data.meniPedi)
    printf("\n");
}

void printTreatmentHeaders()
{
    printf("%-5s\t%-10s\t%-10s\t%-10s\t%-5s\t%-5s\t%-10s\t%-10s\t%-10s\t", "Code", "Type", "Is Active", "Duration", "Price", "Room", "Employee", "Date", "Hour");
}

int writeTreatmentToBFile(FILE* pFile, FILE* pCFile, const Treatment* pTreatment)
{
    int len = (int)strlen(pTreatment->code);
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pTreatment->code, sizeof(char), len, pFile) != len) return 0;

    if (fwrite(&pTreatment->date, sizeof(Date), 1, pFile) != 1) return 0;
    if (fwrite(&pTreatment->duration, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pTreatment->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pTreatment->isActive, sizeof(int), 1, pFile) != 1) return 0;

    len = (int)strlen(pTreatment->pTreatmentRoom->code);
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pTreatment->pTreatmentRoom->code, sizeof(char), len, pFile) != len) return 0;

    if (fwrite(&pTreatment->pTreatmentEmployee->id, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pTreatment->type, sizeof(TreatmentType), 1, pFile) != 1) return 0;

    switch ((int)pTreatment->type)
    {
    case eMassage:
        writeMassageToBFile(pFile, &pTreatment->data.massage);
        break;
    case eHotStones:
        writeHotStonesToBFile(pCFile, &pTreatment->data.hotStones);
        break;
    case eMeniPedi:
        writeMenicurePedicureToBFile(pFile, &pTreatment->data.meniPedi);
        break;
    }

    return 1;
}

int readTreatmentFromBFile(FILE* pFile, FILE* pCFile, Treatment* pTreatment, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
    char roomCode[TOTAL_CODE + 1];
    int employeeId, len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(pTreatment->code, sizeof(char), len, pFile) != len) return 0;
    pTreatment->code[len] = '\0';

    if (fread(&pTreatment->date, sizeof(Date), 1, pFile) != 1) return 0;
    if (fread(&pTreatment->duration, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pTreatment->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pTreatment->isActive, sizeof(int), 1, pFile) != 1) return 0;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(roomCode, sizeof(char), len, pFile) != len) return 0;
    roomCode[len] = '\0';

    if (fread(&employeeId, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pTreatment->type, sizeof(TreatmentType), 1, pFile) != 1) return 0;

    pTreatment->pTreatmentRoom = findRoomByCode(pRoomManager, roomCode);
    pTreatment->pTreatmentEmployee = findEmployeeById(pEmployeeManager, employeeId);

    switch ((int)pTreatment->type)
    {
    case eMassage:
        readMassageFromBFile(pFile, &pTreatment->data.massage);
        break;
    case eHotStones:
        readHotStonesFromBFile(pCFile, &pTreatment->data.hotStones);
        break;
    case eMeniPedi:
        readMenicurePedicureFromBFile(pFile, &pTreatment->data.meniPedi);
        break;
    }

    return 1;
}


int writeTreatmentToTextFile(FILE* pFile, const Treatment* pTreatment)
{
    if (fprintf(pFile, "%s\n", pTreatment->code) < 0) return 0;
    writeDateToTextFile(pFile, &pTreatment->date);
    if (fprintf(pFile, "%d\n", pTreatment->duration) < 0) return 0;
    if (fprintf(pFile, "%d\n", pTreatment->price) < 0) return 0;
    if (fprintf(pFile, "%d\n", pTreatment->isActive) < 0) return 0;
    if (fprintf(pFile, "%s\n", pTreatment->pTreatmentRoom->code) < 0) return 0;
    if (fprintf(pFile, "%d\n", pTreatment->pTreatmentEmployee->id) < 0) return 0;
    if (fprintf(pFile, "%d\n", pTreatment->type) < 0) return 0;

    switch (pTreatment->type)
    {
    case eMassage:
        writeMassageToTextFile(pFile, &pTreatment->data.massage);
        break;

    case eHotStones:
        writeHotStonesToTextFile(pFile, &pTreatment->data.hotStones);
        break;

    case eMeniPedi:
        writeMenicurePedicureToTextFile(pFile, &pTreatment->data.meniPedi);
        break;
    }
    return 1;
}

int readTreatmentFromTextFile(FILE* pFile, Treatment* pTreatment, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
    char roomCode[TOTAL_CODE + 1];
    int employeeId;

    if (!fscanf(pFile, " %s\n", pTreatment->code)) return 0;
    readDateFromTextFile(pFile, &pTreatment->date);

    if (fscanf(pFile, "%d\n", &pTreatment->duration) < 0) return 0;
    if (fscanf(pFile, "%d\n", &pTreatment->price) < 0) return 0;
    if (fscanf(pFile, "%d\n", &pTreatment->isActive) < 0) return 0;
    if (fscanf(pFile, "%s\n", roomCode) < 0) return 0;
    pTreatment->pTreatmentRoom = findRoomByCode(pRoomManager, roomCode);
    if (fscanf(pFile, "%d\n", &employeeId) < 0) return 0;
    pTreatment->pTreatmentEmployee = findEmployeeById(pEmployeeManager, employeeId);
    if (fscanf(pFile, "%d\n", &pTreatment->type) < 0) return 0;

    switch (pTreatment->type)
    {
    case eMassage:
        readMassageFromTextFile(pFile, &pTreatment->data.massage);
        break;

    case eHotStones:
        readHotStonesFromTextFile(pFile, &pTreatment->data.hotStones);
        break;

    case eMeniPedi:
        readMenicurePedicureFromTextFile(pFile, &pTreatment->data.meniPedi);
        break;
    }
    return 1;
}

void updateTreatmentUtilitiesStatus(Treatment* pTreatment)
{
    int currentlyActive;

    time_t rawCurrentTime = time(NULL);
    struct tm* currentTimeStruct = localtime(&rawCurrentTime);
    time_t currentTime = mktime(currentTimeStruct);
    time_t treatmentStartTime = convertToTimeT(&pTreatment->date);
    time_t treatmentEndTime = treatmentStartTime + (pTreatment->duration * 60);

    if (difftime(currentTime, treatmentStartTime) >= 0 && difftime(treatmentEndTime, currentTime) >= 0) {
        currentlyActive = 1;
    }
    else {
        currentlyActive = 0;
    }

    if (pTreatment->pTreatmentRoom) pTreatment->pTreatmentRoom->isBooked = currentlyActive;
    if (pTreatment->pTreatmentEmployee) pTreatment->pTreatmentEmployee->isBooked = currentlyActive;
    pTreatment->isActive = currentlyActive;
}

void freeTreatmentWrapper(void* treatment)
{
    freeTreatment((Treatment*)treatment);
}

/* No need to free HotStones, has only eNums. */
void freeTreatment(Treatment* pTreatment)
{
    CHECK_NULL(pTreatment);
    switch (pTreatment->type) 
    {
    case eMassage:
        freeMassage(&pTreatment->data.massage);
        break;
    case eMeniPedi:
        freeMenicurePedicure(&pTreatment->data.meniPedi);
        break;
    }
    free(pTreatment);
}