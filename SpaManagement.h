#ifndef _SPA_MANAGEMENT_H
#define _SPA_MANAGEMENT_H

#include "TreatmentManager.h"
#include "RoomManager.h"
#include "EmployeeManagment.h"


typedef struct
{
    char* name;
    char* location;
    //opening hours-- what type is this?
    EmployeeManagment* eManager;
    TreatmentManager tManager;
    RoomManager rManger;
}SpaManagment;
int initSpaManagment(SpaManagment* eSpa);
void startTreatment(SpaManagment* eSpa);
int getEmployee(EmployeeManagment* eManager, int role);
void endTreatment(Treatment* pTreatment, Date date, int hour);
int calcRevenue();
int writeToText();
int writeToFile();
int readFromTextFile();
int readFromBinaryFile();


#endif