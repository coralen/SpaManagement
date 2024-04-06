#ifndef _SPA_MANAGER_H
#define _SPA_MANAGER_H

#include "EmployeeManager.h"
#include "TreatmentManager.h"
#include "RoomManager.h"


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
int         getSpaName(char** name);
int         getSpaLocation(char** location);
int         saveSpaToBFile(const SpaManager* pSpaManager, const char* fileName);
int         saveSpaToTextFile(const SpaManager* pSpaManager, const char* fileName);
int         writeSpaToBFile(FILE* pFile, const SpaManager* pSpaManager);
int         initSpaManagerFromBFile(SpaManager* pSpaManager, const char* fileName);
int         initManagerFromTextFile(SpaManager* pSpaManager, const char* fileName);
int         readSpaFromBFile(FILE* pFile, SpaManager* pSpaManager);
int         writeSpaToTextFile(FILE* pFile, const SpaManager* pSpaManager);
int         readSpaFromTextFile(FILE* pFile, SpaManager* pSpaManager);
int         deleteSpaRoom(RoomManager* pRoomManager, TreatmentManager* pTreatmentManager);
int         deleteSpaEmployee(EmployeeManager* pEmployeeManager, TreatmentManager* pTreatmentManager);
int         deleteSpaTreatment(TreatmentManager* pTreatmentManager);
void        getSpaBudget(SpaManager* pSpa);
void        printSpa(const SpaManager* pSpaManager);
void        setSpaDefaults(SpaManager* pSpaManager);
Room*       findAvailableRoom(RoomManager* pRoomManager, TreatmentManager* pTreatmentManager, RoomType type, Date* pDate);
Employee*   findAvailableEmployee(EmployeeManager* pEmployeeManager, TreatmentManager* pTreatmentManager, eEmployeeRole role, Date* pDate);

#endif