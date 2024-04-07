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
    pEmployeeManager->EmployeeArr = (Employee**)realloc(pEmployeeManager->EmployeeArr, (pEmployeeManager->employeeCount+ 1) * sizeof(Employee*));

    if (!pEmployeeManager->EmployeeArr)
    {
        free(pEmployee);
        return 0;
    }

    pEmployeeManager->EmployeeArr[pEmployeeManager->employeeCount] = pEmployee; //adding the pointer to the array
    pEmployeeManager->employeeCount++;
    return 1;
}

void giveEmployeeARaise(EmployeeManager* pEmployeeManager)
{
    int eployeeId, raise;
    Employee* pEmployee;
    int validFlag = 0;

    printf("Please choose id of an available employee:\n");
    printEmployeeArr(pEmployeeManager);
    while (!validFlag)
    {
        scanf("%d", &eployeeId);
        if (!(pEmployee = findEmployeeById(pEmployeeManager, eployeeId))) printf("No employee with this id! try again\n");
        else {
            printf("Enter the raise:\n");
            scanf("%d", &raise);
            giveARaise(pEmployee, raise);
            validFlag = 1;
        }
    }
}
Employee* findEmployeeById(const EmployeeManager* pEmployeeManager, const int id)
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
    {
        if (pEmployeeManager->EmployeeArr[i]->id == id)
            return pEmployeeManager->EmployeeArr[i];
    }
    return NULL;
}

Employee* findEmployeeByRole(const EmployeeManager* pEmployeeManager, const eEmployeeRole role) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) {
        if (!isEmployeeAvailable(pEmployeeManager->EmployeeArr[i]) && pEmployeeManager->EmployeeArr[i]->role == role)
            return pEmployeeManager->EmployeeArr[i];
    }
    return NULL;
}


Employee* findEmployeeBySeniorityAndRole(const EmployeeManager* pEmployeeManager, const int seniority, int role) 
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

int findEmployeeByName(const EmployeeManager* pEmployeeManager, const char* name) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
        if (pEmployeeManager->EmployeeArr[i]->name == name) return i;

    return -1;
}

int deleteEmployee(EmployeeManager* pEmployeeManager, const char* name) 
{
    int employeeIndex = findEmployeeByName(pEmployeeManager, name);
    if (employeeIndex == -1) return 0;
    freeEmployee(pEmployeeManager->EmployeeArr[employeeIndex]);

    if (!(pEmployeeManager->employeeCount - 1))
    {
        free(pEmployeeManager->EmployeeArr);
        pEmployeeManager->EmployeeArr = NULL;
        return 1;
    }

    for (int i = employeeIndex; i < pEmployeeManager->employeeCount - 1; i++)
        pEmployeeManager->EmployeeArr[i] = pEmployeeManager->EmployeeArr[i + 1];

    pEmployeeManager->employeeCount--;

    Employee** tempEmployeeArray = realloc(pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount * sizeof(Employee*));
    if (tempEmployeeArray != NULL) pEmployeeManager->EmployeeArr = tempEmployeeArray;
    else return 0;

    return 1;
}

void printEmployeeArr(const EmployeeManager* pEmployeeManager)
{
    printEmployeeHeaders();
    printf("\n");
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        printEmployee(pEmployeeManager->EmployeeArr[i]);
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

void freeEmployeeManager(EmployeeManager* pEmployeeManager)
{
    CHECK_NULL(pEmployeeManager);
    generalArrayFunction(pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), freeEmployeeWrapper);
    free(pEmployeeManager->EmployeeArr);
}