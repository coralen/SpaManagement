#ifndef _TREATMENT_H
#define _TREATMENT_H

#include <stdio.h>

#include "Helper.h"
#include "Date.h"
#include "RoomManager.h"
#include "EmployeeManager.h"

#include "Massage.h"
#include "HotStones.h"
#include "MenicurePedicure.h"

#define TREATMENT_START_CHARS "T-"


typedef enum { eMassage, eHotStones, eMeniPedi, eNofTreatmentType } TreatmentType;

typedef union {
    Massage massage;
    HotStones hotStones;
    MenicurePedicure meniPedi;
} TreatmentData;

typedef struct {
    char code[TOTAL_CODE + 1];
    Date date;
    int duration;
    int price;
    BOOL isActive;
    Room* pTreatmentRoom;
    Employee* pTreatmentEmployee;
    TreatmentType type;
    TreatmentData data;
} Treatment;

int         initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, Employee* pEmployee, Date* pDate);
int         initMassage(Treatment* pTreatment);
int         initMenicurePedicure(Treatment* pTreatment);
int         writeTreatmentToBFile(FILE* pFile, FILE* pCFile, const Treatment* pTreatment);
int         readTreatmentFromBFile(FILE* pFile, FILE* pCFile, Treatment* pTreatment, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int         writeTreatmentToTextFile(FILE* pFile, const Treatment* pTreatment);
int         readTreatmentFromTextFile(FILE* pFile, Treatment* pTreatment, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
void        getTreatmentCode(char* code);
void        initHotStones(Treatment* pTreatment);
void        freeTreatment(Treatment* pTreatment);
void        freeTreatmentWrapper(void* treatment);
void        printTreatmentTypes();
void        printTreatment(const Treatment* pTreatment);
void        printTreatmentHeaders();
void        printTreatmentWithData(const Treatment* pTreatment, int type);
void        updateTreatmentUtilitiesStatus(Treatment* pTreatment);
const char* getTreatmentTypeString(const int typeNum);
const int   getTreatmentDurationInt(const int typeNum);
const int   getTreatmentPriceInt(const int typeNum);

#endif
