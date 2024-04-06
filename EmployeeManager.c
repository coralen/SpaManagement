#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "EmployeeManager.h"

void initEmployeeManager(EmployeeManager* pEmployeeManager)
{
    pEmployeeManager->EmployeeArr = NULL;
    pEmployeeManager->employeeCount = 0;
}


int addEmployee(EmployeeManager* pEmployeeManager) 
{
    Employee* pEmployee = (Employee*)calloc(1, sizeof(Employee));
    if (!pEmployee) return 0;

    initEmployee(pEmployee);

    if (pEmployeeManager->EmployeeArr == NULL)
        pEmployeeManager->EmployeeArr = (Employee**)realloc(NULL, sizeof(Employee*));
    else {
        pEmployeeManager->EmployeeArr = (Employee**)realloc(pEmployeeManager->EmployeeArr,
            (pEmployeeManager->employeeCount + 1) * sizeof(Employee*));
    }
    // check if we can reduce to one line as we did on Task 2/3.

    if (!pEmployeeManager->EmployeeArr) {
        free(pEmployee);
        printf("Memory allocation failed\n");
        return 0;
    }

    pEmployeeManager->EmployeeArr[pEmployeeManager->employeeCount] = pEmployee; //adding the pointer to the array
    pEmployeeManager->employeeCount++;
    return 1;
}

BOOL isEmployeeAvailable(Employee* pEmployee) 
{
    return pEmployee->isBooked;
}

Employee* findEmployeeById(EmployeeManager* pEmployeeManager, int id)
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) {
        if (pEmployeeManager->EmployeeArr[i]->id == id)
            return pEmployeeManager->EmployeeArr[i];
    }
    return NULL;
}

Employee* findEmployeeByRole(EmployeeManager* pEmployeeManager, eEmployeeRole role) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) {
        if (!isEmployeeAvailable(pEmployeeManager->EmployeeArr[i]) && pEmployeeManager->EmployeeArr[i]->role == role)
            return pEmployeeManager->EmployeeArr[i];
    }
    return NULL;
}


Employee* findEmployeeBySeniorityAndRole(EmployeeManager* pEmployeeManager, int seniority, int role) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
    {
        if (!isEmployeeAvailable(pEmployeeManager->EmployeeArr[i]) && pEmployeeManager->EmployeeArr[i]->seniority == seniority && pEmployeeManager->EmployeeArr[i]->role == role) 
        {
            printEmployee(pEmployeeManager->EmployeeArr[i]);
            return pEmployeeManager->EmployeeArr[i];
        }
    }
    return NULL;
}

int findEmployeeByName(EmployeeManager* pEmployeeManager, char* name) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
        if (pEmployeeManager->EmployeeArr[i]->name == name) return i;

    return -1;
}

void deleteEmployee(EmployeeManager* pEmployeeManager, char* name) 
{
    int employeeIndex = findEmployeeByName(pEmployeeManager, name);
    freeEmployee(pEmployeeManager->EmployeeArr[employeeIndex]); //releasing the info that employee has

    pEmployeeManager->EmployeeArr[employeeIndex] = pEmployeeManager->EmployeeArr[pEmployeeManager->employeeCount - 1]; //changing the pointer in the array to the last employee
    pEmployeeManager->EmployeeArr[pEmployeeManager->employeeCount - 1] = NULL; //last pointer in array points to null and free for reuse when adding an employee
    // check if need to add realloc for EmployeeArr - note that itll effect the addEmployee function (if else)
}

int getEmployee(EmployeeManager* eManager, int role) 
{
    printf("Do you want to choose an employee by seniority? \n0- no \n1- yes\n");
    int choise;
    scanf("%d", &choise);
    if (choise == 0) findEmployeeByRole(eManager, role);
    else if (choise == 1) 
    {
        printf("What seniority do you want?\n");
        int seniority;
        scanf("%d", &seniority);
        findEmployeeBySeniorityAndRole(eManager, seniority, role);
    }
    else printf("choise is invalid");
    return 0;
}

void printEmployeeArr(const EmployeeManager* pEmployeeManager)
{
    printEmployeeHeaders();
    printf("\n");
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        printEmployee(pEmployeeManager->EmployeeArr[i]);
}

void freeEmployeeArr(Employee** EmployeeArr, int size)
{
    generalArrayFunction(*EmployeeArr, size, sizeof(Employee*), (void (*)(void*))freeEmployee);
    free(EmployeeArr);
}

int writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager)
{
    if (fwrite(&pEmployeeManager->employeeCount, sizeof(int), 1, pFile) != 1) return 0;
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        if (!writeEmployeeToBFile(pFile, pEmployeeManager->EmployeeArr[i])) return 0;
    return 1;
}

int readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager)
{
    if (fread(&pEmployeeManager->employeeCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!pEmployeeManager->employeeCount) return 1;
    if (!(pEmployeeManager->EmployeeArr = (Employee**)realloc(pEmployeeManager->EmployeeArr, (pEmployeeManager->employeeCount) * sizeof(Employee*)))) return 0;
    
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
    {
        Employee* pEmployee = (Employee*)calloc(1, sizeof(Employee));
        if (!readEmployeeFromBFile(pFile, pEmployee)) return 0;
        pEmployeeManager->EmployeeArr[i] = pEmployee;
    }
    return 1;
}

int writeEmployeeManagerToTextFile(FILE* pFile, const EmployeeManager* pEmployeeManager)
{
    if (fprintf(pFile, "%d\n", pEmployeeManager->employeeCount) < 0) return 0;
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        if (!writeEmployeeToTextFile(pFile, pEmployeeManager->EmployeeArr[i])) return 0;
    return 1;
}

int readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager)
{
    if (!fscanf(pFile, "%d\n", &pEmployeeManager->employeeCount)) return 0;
    if (!pEmployeeManager->employeeCount) return 1;
    if (!(pEmployeeManager->EmployeeArr = (Employee**)realloc(pEmployeeManager->EmployeeArr, (pEmployeeManager->employeeCount) * sizeof(Employee*)))) return 0;
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
    {
        Employee* pEmployee = (Employee*)calloc(1, sizeof(Employee));
        if (!readEmployeeFromTextFile(pFile, pEmployee)) return 0;
        pEmployeeManager->EmployeeArr[i] = pEmployee;
    }
    return 1;
}