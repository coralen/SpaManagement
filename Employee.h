#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#include <stdio.h>

#include "General.h"
#include "helper.h"

typedef enum {
    eReceptionist, eMasseuse, eNailTechnician, eHotStonesTherapist, eManager, eNofRole
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
int         setEmployeeName(char** name);
int         getEmployeeSalaryInt(int roleNum);
int         writeEmployeeToBFile(FILE* pFile, const Employee* pEmployee);
int         readEmployeeFromBFile(FILE* pFile, Employee* pEmployee);
int         writeEmployeeToTextFile(FILE* pFile, const Employee* pEmployee);
int         readEmployeeFromTextFile(FILE* pFile, Employee* pEmployee);
void        setEmployeeSeniority(Employee* pEmployee);
void        setEmployeeRole(Employee* pEmployee);
void        changeStatus(Employee* pEmployee);
void        setEmployeeSalary(Employee* pEmployee, int salary);
void        giveARaise(Employee* pEmployee, int addition);
void        changeRole(Employee* pEmployee);
void        printEmployee(const Employee* pEmployee);
void        printEmployeeRoles();
void        printEmployeeHeaders();
void        freeEmployee(Employee* employee);
void        freeEmployeeWrapper(void* pEmployee);
void        printEmployeeWrapper(void* pEmployee);
BOOL        isEmployeeAvailable(const Employee* pEmployee);
const char* getEmployeeRoleString(const int roleNum);


#endif