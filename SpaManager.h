#ifndef _SPA_MANAGER_H
#define _SPA_MANAGER_H

#include <stdio.h>

#include "EmployeeManager.h"
#include "TreatmentManager.h"
#include "RoomManager.h"

#define MIN_TREATMENTS_FOR_AWARD 2

typedef enum { eIncreaseBudget, eFireEmployee, eDeleteTreatmant, eStayInOverdraft, eNoOfOverdraftOptions } overdraftOptions;


typedef struct
{
    char* name;
    char* location;
    int budget;
    RoomManager roomManager;
    EmployeeManager employeeManager;
    TreatmentManager treatmentManager;
} SpaManager;


int         initSpaManager(SpaManager* pSpa);
int	        checkRequirments(const TreatmentManager* pTreatmentManager, const RoomManager* pRoomManager, const EmployeeManager* pEmployeeManager);
int         addTreatment(TreatmentManager* pTreatmentManager, const RoomManager* pRoomManager, const EmployeeManager* pEmployeeManager);
int         initManagers(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int         setSpaName(char** name);
int         setSpaLocation(char** location);
int         saveSpaToBFile(const SpaManager* pSpaManager, const char* fileName, const char* cFileName);
int         saveSpaToTextFile(const SpaManager* pSpaManager, const char* fileName);
int         writeSpaToBFile(FILE* pFile, FILE* pCFile, const SpaManager* pSpaManager);
int         initSpaManagerFromBFile(SpaManager* pSpaManager, const char* fileName, const char* cFileName);
int         initSpaManagerFromTextFile(SpaManager* pSpaManager, const char* fileName);
int         readSpaFromBFile(FILE* pFile, FILE* pCFile, SpaManager* pSpaManager);
int         writeSpaToTextFile(FILE* pFile, const SpaManager* pSpaManager);
int         readSpaFromTextFile(FILE* pFile, SpaManager* pSpaManager);
int         deleteRoomFromSpa(RoomManager* pRoomManager, const TreatmentManager* pTreatmentManager);
int         deleteEmployeeFromSpa(EmployeeManager* pEmployeeManager, const TreatmentManager* pTreatmentManager);
int         doesEmployyeDeserveAnAward(Employee* employee, TreatmentManager* treatmentManager);
void        increaseSpaBudget(SpaManager* pSpaManager);
void        freeSpaManager(SpaManager* pSpaManager);
void        setSpaBudget(SpaManager* pSpa);
void        printSpa(const SpaManager* pSpaManager);
void        setSpaDefaults(SpaManager* pSpaManager);
void        calcSpaRevenue(SpaManager* pSpaManager);
void        printOverdraftOptions();
void        emplyeeAwardSystem(EmployeeManager* employeeManager, TreatmentManager* treatmentManager);
Room*       findAvailableRoom(const RoomManager* pRoomManager, const TreatmentManager* pTreatmentManager, const RoomType type, const Date* pDate);
Employee*   findAvailableEmployee(const EmployeeManager* pEmployeeManager, const TreatmentManager* pTreatmentManager, const eEmployeeRole role, const Date* pDate);
const char* getOverdraftOptionsString(const int optionNum);

#endif