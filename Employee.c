#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Employee.h"

static int idCounter = 1;
static const char* employeeRolesString[eNofRole] = { "Receptionist", "Masseuse", "NailTechnician", "HotStonesTherapist" , "Manager" };
static const int employeeSalaryInt[eNofRole] = { 30, 70, 70, 100, 150 };


int initEmployee(Employee* pEmployee) 
{ 
    getEmployeeName(&pEmployee->name);
    pEmployee->id = getEmployeeId();
    getEmployeeRole(pEmployee);
    getEmployeeSeniority(pEmployee);
    pEmployee->salary = getEmployeeSalaryInt(pEmployee->role);
    BOOL isBooked = 0;

    return 1;
}

int getEmployeeId() 
{
    return idCounter++;
}

int getEmployeeName(char** name)
{
    char inputName[MAX_STRING];

    printf("Enter the first and last name of the new employee: \n");
    scanf(SCANF_FORMAT, inputName);
    while (getchar() != '\n');
    if (!(*name = (char*)malloc((strlen(inputName) + 1) * sizeof(char)))) return 0;
    strcpy(*name, inputName);

    return 1;
}

void getEmployeeRole(Employee* pEmployee)
{
    printf("Enter the role of the new employee, the options are: \n");
    printEmployeeRoles();
    int numRole;
    scanf("%d", &numRole);

    if (numRole >= 0 && numRole < eNofRole)
    {
        pEmployee->role = numRole;
        printf("Role set to: %s\n", employeeRolesString[pEmployee->role]);
    }
    else printf("Invalid role number\n");
}

void getEmployeeSeniority(Employee* pEmployee)
{
    printf("Enter the years of experience: \n");
    scanf("%d", &pEmployee->seniority);
}

int getEmployeeSalaryInt(int roleNum)
{
    return employeeSalaryInt[roleNum];
}

void giveARaise(Employee* pEmployee, int newSalary)
{
    pEmployee->salary = pEmployee->salary + newSalary;
}

BOOL isEmployeeAvailable(Employee* pEmployee)
{
    return pEmployee->isBooked;
}

void setSalary(Employee* pEmployee, int salary) 
{
    printf("Currently, the salary is %d enter the new salary of the employee: \n", salary);
    scanf("%d", &salary);
    pEmployee->salary = salary;
}

void changeStatus(Employee* pEmployee) 
{
    if (!pEmployee->isBooked) pEmployee->isBooked = 1;
    else pEmployee->isBooked = 0;
}

void changeRole(Employee* pEmployee) 
{
    printf("Role set to: %s\n", getEmployeeRoleString(pEmployee->role));
    printf("Enter the new role of the employee, the options are: \n");
    printEmployeeRoles();

    int numRole;
    scanf("%d", &numRole);
    if (numRole >= 0 && numRole < eNofRole) {
        pEmployee->role = numRole;
        printf("Role set to: %s\n", getEmployeeRoleString(pEmployee->role));
    }
    else {
        printf("Invalid role number\n");
    }
}

void printEmployee(const Employee* pEmployee) 
{
    printf("%-10d\t%-10s\t%-10d\t%-10d\t%-20s\t%-10s\t\n", pEmployee->id, pEmployee->name, pEmployee->salary, pEmployee->seniority, getEmployeeRoleString(pEmployee->role), getStatusString(pEmployee->isBooked));
}

void printEmployeeHeaders()
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t%-20s\t%-10s\t", "ID", "Name", "Salary", "Seniority", "Role", "Status");
}

void printEmployeeRoles()
{
    for (int i = 0; i < eNofRole; i++)
        printf("%d - %s\n", i, getEmployeeRoleString(i));
}

const char* getEmployeeRoleString(int roleNum)
{
    return employeeRolesString[roleNum];
}

int writeEmployeeToBFile(FILE* pFile, Employee* pEmployee)
{
    int len = (int)(strlen(pEmployee->name) + 1);
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pEmployee->name, sizeof(char), len, pFile) != len) return 0;

    if (fwrite(&pEmployee->id, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pEmployee->salary, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pEmployee->seniority, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pEmployee->role, sizeof(eEmployeeRole), 1, pFile) != 1) return 0;
    if (fwrite(&pEmployee->isBooked, sizeof(BOOL), 1, pFile) != 1) return 0;

    return 1;
}

int readEmployeeFromBFile(FILE* pFile, Employee* pEmployee)
{
    int len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (!(pEmployee->name = (char*)malloc(len * sizeof(char)))) return 0;
    if (fread(pEmployee->name, sizeof(char), len, pFile) != len) return 0;

    if (fread(&pEmployee->id, sizeof(int), 1, pFile) != 1) return 0;
    if (pEmployee->id >= idCounter) idCounter = pEmployee->id + 1;
    if (fread(&pEmployee->salary, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pEmployee->seniority, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pEmployee->role, sizeof(eEmployeeRole), 1, pFile) != 1) return 0;
    if (fread(&pEmployee->isBooked, sizeof(BOOL), 1, pFile) != 1) return 0;

    return 1;
}


int writeEmployeeToTextFile(FILE* pFile, Employee* pEmployee)
{
    if (fprintf(pFile, "%s\n", pEmployee->name) < 0) return 0;
    if (fprintf(pFile, "%d\n", pEmployee->id) < 0) return 0;
    if (fprintf(pFile, "%d\n", pEmployee->salary) < 0) return 0;
    if (fprintf(pFile, "%d\n", pEmployee->seniority) < 0) return 0;
    if (fprintf(pFile, "%d\n", pEmployee->role) < 0) return 0;
    if (fprintf(pFile, "%d\n", pEmployee->isBooked) < 0) return 0;

    return 1;
}

int readEmployeeFromTextFile(FILE* pFile, Employee* pEmployee)
{
    char tmpName[MAX_STRING] = { 0 };

    if (!fscanf(pFile, " %[^\n]\n", tmpName)) return 0;
    pEmployee->name = strdup(tmpName);

    if (!fscanf(pFile, "%d\n", &pEmployee->id)) return 0;
    if (pEmployee->id >= idCounter) idCounter = pEmployee->id + 1;
    if (!fscanf(pFile, "%d\n", &pEmployee->salary)) return 0;
    if (!fscanf(pFile, "%d\n", &pEmployee->seniority)) return 0;
    if (!fscanf(pFile, "%d\n", &pEmployee->role)) return 0;
    if (!fscanf(pFile, "%d\n", &pEmployee->isBooked)) return 0;

    return 1;
}

void freeEmployee(Employee* pEmployee) 
{
    if (!pEmployee) return; 
    free(pEmployee->name);
    free(pEmployee);
}

void freeEmployeeWrapper(void* pEmployee) 
{
    Employee** employee = (Employee**)pEmployee;
    freeEmployee(*employee);
}