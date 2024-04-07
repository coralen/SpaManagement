#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#pragma once

#include "General.h"
#include "helper.h"

typedef enum {
    eReceptionist, eMasseuse, eNailTechnician, eHotStonesTherapist, eMnager, eNofRole
} eEmployeeRole;

typedef struct
{
    char* name;
    int id;
    int salary;
    int seniority;
    eEmployeeRole role;
    BOOL isBooked;
} Employee;


int         initEmployee(Employee* pEmployee);
int         getEmployeeId();
int         getEmployeeName(char** name);
int         getEmployeeSalaryInt(int roleNum);
int         writeEmployeeToBFile(FILE* pFile, Employee* pEmployee);
int         readEmployeeFromBFile(FILE* pFile, Employee* pEmployee);
int         writeEmployeeToTextFile(FILE* pFile, Employee* pEmployee);
int         readEmployeeFromTextFile(FILE* pFile, Employee* pEmployee);
void        getEmployeeSeniority(Employee* pEmployee);
void        getEmployeeRole(Employee* pEmployee);
void        changeStatus(Employee* pEmployee);
void        setSalary(Employee* pEmployee, int salary);
void        giveARaise(Employee* pEmployee, int newSalary);
void        changeRole(Employee* pEmployee);
void        printEmployee(const Employee* pEmployee);
void        printEmployeeRoles();
void        printEmployeeHeaders();
void        freeEmployee(Employee* employee);
void        freeEmployeeWrapper(void* pEmployee);
BOOL        isEmployeeAvailable(Employee* pEmployee);
const char* getEmployeeRoleString(int roleNum);


#endif