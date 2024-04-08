#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#pragma once

#include "General.h"
#include "Helper.h"

typedef enum {
    eReceptionist, eMasseuse, eNailTechnician, eHotStonesTherapist, eManager, eNofRole
} eEmployeeRole;

typedef enum {
    eNone, eEmployeesRole, eName, eId
} eSort;

static const char* sortFields[NUM_OF_SORT_TYPES] = { "Employee Role", "name", "id" };

typedef struct
{
    char* name;
    int id; //b-search
    int salary;
    int seniority;
    eEmployeeRole role;
    BOOL isBooked;
    eSort		sortField;
} Employee;

int compareByRole(const void* a, const void* b);
int compareByName(const void* a, const void* b);
int compareById(const void* a, const void* b);
int         initEmployee(Employee* pEmployee);
int         getEmployeeId();
int         setEmployeeName(char** name);
int         getEmployeeSalaryInt(int roleNum);
int         writeEmployeeToBFile(FILE* pFile, const Employee* pEmployee);
int         readEmployeeFromBFile(FILE* pFile, Employee* pEmployee);
int         writeEmployeeToTextFile(FILE* pFile, const Employee* pEmployee);
int         readEmployeeFromTextFile(FILE* pFile, Employee* pEmployee);
void        setEmployeeSeniority(Employee* pEmployee);
void        setEmployeeRole(Employee* pEmployee);
int returnEmployeeId(Employee* pEmployee);

//why not in use?
void        changeStatus(Employee* pEmployee);
void        setEmployeeSalary(Employee* pEmployee, int salary);
void        changeRole(Employee* pEmployee);

void        giveARaise(Employee* pEmployee, int bonus);
void        printEmployee(const Employee* pEmployee);
void        printEmployeeRoles();
void        printEmployeeHeaders();
void        freeEmployee(Employee* employee);
void        freeEmployeeWrapper(void* pEmployee);
void        printEmployeeWrapper(void* pEmployee);
BOOL        isEmployeeAvailable(const Employee* pEmployee);
const char* getEmployeeRoleString(const int roleNum);


#endif