#ifndef _EMPLOYEEMANAGMENT_H
#define _EMPLOYEEMANAGMENT_H

#pragma once

#include "General.h"
#include "Employee.h"

typedef struct
{
    Employee** EmployeeArr;
    int employeeCount;
} EmployeeManager;

/* No use */
int         getEmployee(const EmployeeManager* eManager, int role); 

int         addEmployee(EmployeeManager* pEmployeeManager);
int         findEmployeeByName(const EmployeeManager* pEmployeeManager, const char* name);
int         writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         writeEmployeeManagerToTextFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         deleteEmployee(EmployeeManager* pEmployeeManager, const char* name);
void        initEmployeeManager(EmployeeManager* pEmployeeManager);
void        printEmployeeArr(const EmployeeManager* pEmployeeManager);
void        freeEmployeeManager(EmployeeManager* pEmployeeManager);
void        giveEmployeeARaise(EmployeeManager* pEmployeeManager);
Employee*   findEmployeeByRole(const EmployeeManager* pEmployeeManager, const eEmployeeRole role);
Employee*   findEmployeeBySeniorityAndRole(const EmployeeManager* pEmployeeManager, const int seniority, int role);
Employee*   findEmployeeById(const EmployeeManager* pEmployeeManager, const int id);


#endif