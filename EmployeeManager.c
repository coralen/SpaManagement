#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "EmployeeManager.h"

static const char* sortFieldsString[eNone] = { "Employee Role", "name", "id" };

void initEmployeeManager(EmployeeManager* pEmployeeManager)
{
    pEmployeeManager->EmployeeArr = NULL;
    pEmployeeManager->employeeCount = 0;
    pEmployeeManager->sortField = eNone;
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

void chooseEmployeeId(Employee* pEmployee, const EmployeeManager* pEmployeeManager)
{
    do
    {
        scanf("%d", &pEmployee->id);
    } while (!findEmployeeById(pEmployeeManager, pEmployee->id));

}

void giveEmployeeARaise(EmployeeManager* pEmployeeManager)
{
    int raise;
    Employee* pEmployee;
    int validFlag = 0;

    pEmployee = (Employee*)calloc(1, sizeof(Employee));

    while (!validFlag)
    {
        printf("Please choose id of an available employee:\n");
        printEmployeeArr(pEmployeeManager);
        chooseEmployeeId(pEmployee, pEmployeeManager);
        if (!(pEmployee = findEmployeeById(pEmployeeManager, pEmployee->id))) printf("No employee with this id! try again\n");
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

int findEmployeeByRole(const EmployeeManager* pEmployeeManager, const eEmployeeRole role)
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) {
        if (!isEmployeeAvailable(pEmployeeManager->EmployeeArr[i]) && pEmployeeManager->EmployeeArr[i]->role == role)
            return i;
    }
    return -1;
}


int findEmployeeBySeniorityAndRole(const EmployeeManager* pEmployeeManager, const int seniority, int role)
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
    {
        if (!isEmployeeAvailable(pEmployeeManager->EmployeeArr[i]) && pEmployeeManager->EmployeeArr[i]->seniority == seniority && pEmployeeManager->EmployeeArr[i]->role == role) 
        {
            printEmployee(pEmployeeManager->EmployeeArr[i]);
            return i;
        }
    }
    return -1;
}

int findEmployeeByName(const EmployeeManager* pEmployeeManager, const char* name) 
{
    for (int i = 0; i < pEmployeeManager->employeeCount; i++) 
        if (pEmployeeManager->EmployeeArr[i]->name == name) return i;

    return -1;
}

int deleteEmployee(EmployeeManager* pEmployeeManager, const int id) 
{
    int employeeIndex = findEmployeeById(pEmployeeManager, id)->id;
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

const char* getSortFieldsString(const int sortNum)
{
    return sortFieldsString[sortNum];
}

void printEmployeeSorts()
{
    for (int i = 0; i < eNone; i++)
        printf("%d - %s\n", i, getSortFieldsString(i));
}

void printEmployeeArr(const EmployeeManager* pEmployeeManager)
{
    printEmployeeHeaders();
    printf("\n");
    generalArrayFunction(pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), printEmployeeWrapper);
}

int writeEmployeeManagerToBFile(FILE* pFile, const EmployeeManager* pEmployeeManager)
{
    if (fwrite(&pEmployeeManager->employeeCount, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pEmployeeManager->sortField, sizeof(eSort), 1, pFile) != 1) return 0;
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        if (!writeEmployeeToBFile(pFile, pEmployeeManager->EmployeeArr[i])) return 0;
    return 1;
}

int readEmployeeManagerFromBFile(FILE* pFile, EmployeeManager* pEmployeeManager)
{
    if (fread(&pEmployeeManager->employeeCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!pEmployeeManager->employeeCount) return 1;
    if (!(pEmployeeManager->EmployeeArr = (Employee**)realloc(pEmployeeManager->EmployeeArr, (pEmployeeManager->employeeCount) * sizeof(Employee*)))) return 0;
    
    if (fread(&pEmployeeManager->sortField, sizeof(eSort), 1, pFile) != 1) return 0;
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
    if (fprintf(pFile, "%d\n", pEmployeeManager->sortField) < 0) return 0;
    for (int i = 0; i < pEmployeeManager->employeeCount; i++)
        if (!writeEmployeeToTextFile(pFile, pEmployeeManager->EmployeeArr[i])) return 0;
    return 1;
}

int readEmployeeManagerFromTextFile(FILE* pFile, EmployeeManager* pEmployeeManager)
{
    if (!fscanf(pFile, "%d\n", &pEmployeeManager->employeeCount)) return 0;
    if (!fscanf(pFile, "%d\n", (int*)&pEmployeeManager->sortField)) return 0;
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


void sortEmployees(EmployeeManager* emmployeeManager)
{
    int option;
    printf("\n\n");
    do {
        printf("Base on what field do you want to sort?\n");
        printEmployeeSorts();
        scanf("%d", &option);
    } while (option < -1 || option > eNone);

    emmployeeManager->sortField = (eSort)option;

    switch ((int)emmployeeManager->sortField)
    {
    case eEmployeesRole:
        qsort(emmployeeManager->EmployeeArr, emmployeeManager->employeeCount, sizeof(Employee*), compareByRole);
        break;

    case eName:
        qsort(emmployeeManager->EmployeeArr, emmployeeManager->employeeCount, sizeof(Employee*), compareByName);
        break;

    case eId:
        qsort(emmployeeManager->EmployeeArr, emmployeeManager->employeeCount, sizeof(Employee*), compareById);
        break;
    }

}

void findEmployee(const EmployeeManager* pEmployeeManager)
{
    if (pEmployeeManager->sortField == eNone) 
    {
        printf("The search cannot be performed, array not sorted\n");
        return;
    }

    Employee** found = NULL;
    Employee tmpEmployee;
    Employee* pTmpEmployee = &tmpEmployee;

    switch ((int)pEmployeeManager->sortField) 
    {
    case eEmployeesRole:
        printf("Search by Role: ");
        setEmployeeRole(&tmpEmployee);
        found = bsearch(&pTmpEmployee, pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), compareByRole);
        break;
    case eName:
        printf("Search by Name: ");
        setEmployeeName(&tmpEmployee.name);
        found = bsearch(&pTmpEmployee, pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), compareByName);
        break;
    case eId:
        printf("Search by ID: ");
        chooseEmployeeId(&tmpEmployee, pEmployeeManager);
        found = bsearch(&pTmpEmployee, pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), compareById);
        break;
    }

    if (found) {
        printf("Employee found!\n");
        printEmployeeHeaders();
        printf("\n");
        printEmployee(*found);
        printf("\n");
    }
    else {
        printf("Employee was not found\n");
    }
}

void freeEmployeeManager(EmployeeManager* pEmployeeManager)
{
    CHECK_NULL(pEmployeeManager);
    generalArrayFunction(pEmployeeManager->EmployeeArr, pEmployeeManager->employeeCount, sizeof(Employee*), freeEmployeeWrapper);
    free(pEmployeeManager->EmployeeArr);
}