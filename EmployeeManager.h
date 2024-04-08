#ifndef _EMPLOYEEMANAGMENT_H
#define _EMPLOYEEMANAGMENT_H

#include <stdio.h>

#include "General.h"
#include "Employee.h"

typedef enum {
    eEmployeesRole, eName, eId, eNone
} eSort;

typedef struct
{
    Employee** EmployeeArr;
    int employeeCount;
    eSort sortField;
} EmployeeManager;

int         addEmployee(EmployeeManager* pEmployeeManager);
int         findEmployeeByName(const EmployeeManager* pEmployeeManager, const char* name);
int         writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         writeEmployeeManagerToTextFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         deleteEmployee(EmployeeManager* pEmployeeManager, const int id);
void        chooseEmployeeId(Employee* pEmployee, const EmployeeManager* pEmployeeManager);
void        initEmployeeManager(EmployeeManager* pEmployeeManager);
void        printEmployeeArr(const EmployeeManager* pEmployeeManager);
void        freeEmployeeManager(EmployeeManager* pEmployeeManager);
void        giveEmployeeARaise(EmployeeManager* pEmployeeManager);
void        findEmployee(const EmployeeManager* pEmployeeManager);
void        printEmployeeSorts();
void        sortEmployees(EmployeeManager* emmployeeManager);
int   findEmployeeByRole(const EmployeeManager* pEmployeeManager, const eEmployeeRole role);
int   findEmployeeBySeniorityAndRole(const EmployeeManager* pEmployeeManager, const int seniority, int role);
Employee*   findEmployeeById(const EmployeeManager* pEmployeeManager, const int id);
const char* getSortFieldsString(const int sortNum);

#endif