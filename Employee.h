#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

#pragma once

#include "General.h"
#include "helper.h"

typedef enum {
    eReceptionist, eMasseuse, eNailTechnician, eHotStonesTherapist, eMnager, eNofRole
} eEmployeeRole;

static const char* EmployeeRole[eNofRole]
        = { "Receptionist", "Masseuse", "NailTechnician", "HotStonesTherapist" , "Manager"};

typedef enum {Busy, Available} STATUS;

typedef struct
{
    char* name;
    int baseSalary;
    int seniority;
    eEmployeeRole role;
    STATUS status;
}Employee;

//all the functions work well

int initEmployee(Employee* pEmployee);
int getNameRoleSeniority(Employee* pEmployee, char* name,eEmployeeRole role, int seniority);
int setSalary(Employee* pEmployee, int salary);
int changeStatus(Employee* pEmployee);
void changeRole(Employee* pEmployee);
void printEmployee(const Employee* pEmployee);
int freeEmployee(Employee* employee);

#endif