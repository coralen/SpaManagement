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

int         getEmployee(EmployeeManager* eManager, int role);
int         addEmployee(EmployeeManager* pEmployeeManager);
int         addEmployee(EmployeeManager* pEmployeeManager);
int         findEmployeeByName(EmployeeManager* pEmployeeManager, char* name);
int         writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         writeEmployeeManagerToTextFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager);
BOOL        isEmployeeAvailable(Employee* pEmployee);
Employee*   findEmployeeByRole(EmployeeManager* pEmployeeManager, eEmployeeRole role);
Employee*   findEmployeeBySeniorityAndRole(EmployeeManager* pEmployeeManager, int seniority, int role);
Employee*   findEmployeeById(EmployeeManager* pEmployeeManager, int id);
void        initEmployeeManager(EmployeeManager* pEmployeeManager);
void        deleteEmployee(EmployeeManager* pEmployeeManager, char* name);
void        printEmployeeArr(const EmployeeManager* pEmployeeManager);
void	    freeEmployeeArr(Employee** EmployeeArr, int size);


#endif