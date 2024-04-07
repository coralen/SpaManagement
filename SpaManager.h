#ifndef _SPA_MANAGER_H
#define _SPA_MANAGER_H

#include "EmployeeManager.h"
#include "TreatmentManager.h"
#include "RoomManager.h"

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
int	        checkRequirments(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int         addTreatment(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int         initManagers(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int         setSpaName(char** name);
int         setSpaLocation(char** location);
int         saveSpaToBFile(const SpaManager* pSpaManager, const char* fileName, const char* cFileName);
int         saveSpaToTextFile(const SpaManager* pSpaManager, const char* fileName);
int         writeSpaToBFile(FILE* pFile, FILE* pCFile, const SpaManager* pSpaManager);
int         initSpaManagerFromBFile(SpaManager* pSpaManager, const char* fileName, const char* cFileName);
int         initManagerFromTextFile(SpaManager* pSpaManager, const char* fileName);
int         readSpaFromBFile(FILE* pFile, FILE* pCFile, SpaManager* pSpaManager);
int         writeSpaToTextFile(FILE* pFile, const SpaManager* pSpaManager);
int         readSpaFromTextFile(FILE* pFile, SpaManager* pSpaManager);
int         deleteRoomFromSpa(RoomManager* pRoomManager, TreatmentManager* pTreatmentManager);
int         deleteEmployeeFromSpa(EmployeeManager* pEmployeeManager, TreatmentManager* pTreatmentManager);
int         deleteTreatmentFromSpa(TreatmentManager* pTreatmentManager);
void        increaseSpaBudget(SpaManager* pSpaManager);
void        freeSpaManager(SpaManager* pSpaManager);
void        setSpaBudget(SpaManager* pSpa);
void        printSpa(const SpaManager* pSpaManager);
void        setSpaDefaults(SpaManager* pSpaManager);
void        calcSpaRevenue(SpaManager* pSpaManager);
void        printOverdraftOptions();
Room*       findAvailableRoom(RoomManager* pRoomManager, TreatmentManager* pTreatmentManager, RoomType type, Date* pDate);
Employee*   findAvailableEmployee(EmployeeManager* pEmployeeManager, TreatmentManager* pTreatmentManager, eEmployeeRole role, Date* pDate);
const char* getOverdraftOptionsString(int optionNum);

#endif