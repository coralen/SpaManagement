#ifndef _EMPLOYEEMANAGMENT_H
#define _EMPLOYEEMANAGMENT_H

#pragma once

#include "General.h"
#include "Employee.h"

typedef struct
{
    Employee**	EmployeeArr;
    int employeeCount;
}EmployeeManagment;

//all the functions work

void initEmployeeManagment(EmployeeManagment* pEmployeeManagment);
STATUS isEmployeeAvailable(Employee* pEmployee);
Employee* findEmployeeByRole(EmployeeManagment* pEmployeeManagment, eEmployeeRole role);
Employee* findEmployeeBySeniorityAndRole(EmployeeManagment* pEmployeeManagment, int seniority, int role);
int addEmployee(EmployeeManagment* pEmployeeManagment);
void deleteEmployee(EmployeeManagment* pEmployeeManagment, char* name);
int giveARaise(Employee* pEmployee,int newSalary);
void printEmployeeManagement(const EmployeeManagment* pEmployeeManagment);
void	freeEmployeeArr(Employee** EmployeeArr, int size);


#endif