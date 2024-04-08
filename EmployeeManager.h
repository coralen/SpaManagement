#ifndef _EMPLOYEEMANAGMENT_H
#define _EMPLOYEEMANAGMENT_H

#include <stdio.h>

#include "General.h"
#include "Employee.h"

typedef enum { eGiveARaise, eChangeARole, eNofAwardOptions } AwardOptions;
typedef enum { eAwardName, eAwardRole, eAwardRoleAndSeniority, eNoOfSearchEmployeeAward } SearchEmployeeAwardOptions;


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
int         writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         writeEmployeeManagerToTextFile(FILE* pFile, const EmployeeManager* pEmployeeManager);
int         readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager);
int         deleteEmployee(EmployeeManager* pEmployeeManager, const int id);
void        chooseEmployeeId(Employee* pEmployee, const EmployeeManager* pEmployeeManager);
void        initEmployeeManager(EmployeeManager* pEmployeeManager);
void        printEmployeeArr(const EmployeeManager* pEmployeeManager);
void        freeEmployeeManager(EmployeeManager* pEmployeeManager);
void        giveEmployeeARaise(Employee* pEmployee, EmployeeManager* pEmployeeManager);
void        findEmployee(const EmployeeManager* pEmployeeManager);
void        printEmployeeSorts();
void        printAwardOptions();
void        sortEmployees(EmployeeManager* emmployeeManager);
void        giveEmployeeAward(Employee* pEmployee, EmployeeManager* pEmployeeManager);
Employee*   findEmployeeByName(const EmployeeManager* pEmployeeManager, const char* name);
Employee*   chooseEmployeeForAward(EmployeeManager* employeeManager);
Employee*   findEmployeeByRole(const EmployeeManager* pEmployeeManager, const eEmployeeRole role);
Employee*   findEmployeeBySeniorityAndRole(const EmployeeManager* pEmployeeManager, const int seniority, int role);
Employee*   findEmployeeById(const EmployeeManager* pEmployeeManager, const int id);
const char* getSortFieldsString(const int sortNum);
const char* getAwardOptions(const int optionNum);
const char* getSearchEmployeeAwardOptions(const int optionNum);
#endif