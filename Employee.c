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
    setEmployeeName(&pEmployee->name);
    pEmployee->id = getEmployeeId();
    setEmployeeRole(pEmployee);
    setEmployeeSeniority(pEmployee);
    pEmployee->salary = getEmployeeSalaryInt(pEmployee->role);
    BOOL isBooked = 0;

    return 1;
}

int getEmployeeId() 
{
    return idCounter++;
}

int setEmployeeName(char** name)
{
    char inputName[MAX_STRING];

    printf("Enter the first and last name of the new employee: \n");
    scanf(SCANF_FORMAT, inputName);
    while (getchar() != '\n');
    if (!(*name = (char*)malloc((strlen(inputName) + 1) * sizeof(char)))) return 0;
    strcpy(*name, inputName);
    capitalFirst(*name);

    return 1;
}

void setEmployeeRole(Employee* pEmployee)
{
    printf("Enter the role of the new employee, the options are: \n");
    printEmployeeRoles();
    int numRole;
    scanf("%d", &numRole);

    if (numRole >= 0 && numRole < eNofRole)
    {
        pEmployee->role = numRole;
        //printf("Role set to: %s\n", employeeRolesString[pEmployee->role]); // consider deleting cause we are using this in sort function
    }
    else printf("Invalid role number\n");
}

void setEmployeeSeniority(Employee* pEmployee)
{
    printf("Enter the years of experience: \n");
    scanf("%d", &pEmployee->seniority);
}

int getEmployeeSalaryInt(int roleNum)
{
    return employeeSalaryInt[roleNum];
}

void giveARaise(Employee* pEmployee, int addition)
{
    pEmployee->salary = pEmployee->salary + addition;
}

BOOL isEmployeeAvailable(const Employee* pEmployee)
{
    return pEmployee->isBooked;
}

void setEmployeeSalary(Employee* pEmployee, int salary) 
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

void printEmployeeWrapper(void* pEmployee)
{
    const Employee** employee = (const Employee**)pEmployee;
    printEmployee(*employee);
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

const char* getEmployeeRoleString(const int roleNum)
{
    return employeeRolesString[roleNum];
}

int writeEmployeeToBFile(FILE* pFile, const Employee* pEmployee)
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


int writeEmployeeToTextFile(FILE* pFile, const Employee* pEmployee)
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

int compareByRole(const void* employeeA, const void* employeeB)
{
    const Employee* empA = *(const Employee**)employeeA;
    const Employee* empB = *(const Employee**)employeeB;
    return (empA->role - empB->role);
}

int compareByName(const void* employeeA, const void* employeeB)
{
    const Employee* empA = *(const Employee**)employeeA;
    const Employee* empB = *(const Employee**)employeeB;
    return strcmp(empA->name, empB->name);
}

int compareById(const void* employeeA, const void* employeeB)
{
    const Employee* empA = *(const Employee**)employeeA;
    const Employee* empB = *(const Employee**)employeeB;
    return (empA->id - empB->id);
}

void freeEmployee(Employee* pEmployee) 
{
    CHECK_NULL(pEmployee);
    free(pEmployee->name);
    free(pEmployee);
}

void freeEmployeeWrapper(void* pEmployee) 
{
    Employee** employee = (Employee**)pEmployee;
    freeEmployee(*employee);
}