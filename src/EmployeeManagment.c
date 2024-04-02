#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "EmployeeManagment.h"

void initEmployeeManagment(EmployeeManagment* pEmployeeManagment){
    pEmployeeManagment->EmployeeArr=NULL;
    pEmployeeManagment->employeeCount=0;
}

int addEmployee(EmployeeManagment* pEmployeeManagment){
    Employee* pEmployee = (Employee*)calloc(1, sizeof(Employee));
    if (!pEmployee) return 0;

    initEmployee(pEmployee);
printf("init is done");

    if (pEmployeeManagment->EmployeeArr == NULL) {
        pEmployeeManagment->EmployeeArr = (Employee**)realloc(NULL, sizeof(Employee*));
    } else {
        pEmployeeManagment->EmployeeArr = (Employee**)realloc(pEmployeeManagment->EmployeeArr,
                                                              (pEmployeeManagment->employeeCount + 1) * sizeof(Employee *));
    }
    printf("what??");
    if (!pEmployeeManagment->EmployeeArr) {
        free(pEmployee);
        printf("Memory allocation failed\n");
        return 0;
    }

    printf("what");
    pEmployeeManagment->EmployeeArr[pEmployeeManagment->employeeCount] = pEmployee; //adding the pointer to the array
    pEmployeeManagment->employeeCount++;
    printf("Employee added succesfully");
    return 1;
}

STATUS isEmployeeAvailable(Employee* pEmployee){
     return pEmployee->status;
}

Employee* findEmployeeByRole(EmployeeManagment* pEmployeeManagment, eEmployeeRole role){
    for (int i=0; i<pEmployeeManagment->employeeCount; i++) {
        if (!isEmployeeAvailable(pEmployeeManagment->EmployeeArr[i]) &&
            pEmployeeManagment->EmployeeArr[i]->role == role) {
            printEmployee(pEmployeeManagment->EmployeeArr[i]);
            return pEmployeeManagment->EmployeeArr[i];
        }
    }
    printf("No Employee was found");
    return NULL;
}


Employee* findEmployeeBySeniorityAndRole(EmployeeManagment* pEmployeeManagment, int seniority, int role){
    for (int i=0; i<pEmployeeManagment->employeeCount; i++){
        if (!isEmployeeAvailable(pEmployeeManagment->EmployeeArr[i]) && pEmployeeManagment->EmployeeArr[i]->seniority==seniority && pEmployeeManagment->EmployeeArr[i]->role == role){
            printEmployee(pEmployeeManagment->EmployeeArr[i]);
            return pEmployeeManagment->EmployeeArr[i];
        }
    }
    printf("No Employee was found");
    return NULL;
}

int findEmployeeByName(EmployeeManagment* pEmployeeManagment, char* name){
    for (int i=0; i<pEmployeeManagment->employeeCount; i++){
        if (pEmployeeManagment->EmployeeArr[i]->name==name){
            return i;
        }
    }
    printf("No Employee was found");
    return -1;
}

void deleteEmployee(EmployeeManagment* pEmployeeManagment, char* name){
   int employeeIndex= findEmployeeByName(pEmployeeManagment, name);
    freeEmployee(pEmployeeManagment->EmployeeArr[employeeIndex]); //releasing the info that employee has

    pEmployeeManagment->EmployeeArr[employeeIndex]=pEmployeeManagment->EmployeeArr[pEmployeeManagment->employeeCount-1]; //changing the pointer in the array to the last employee
    pEmployeeManagment->EmployeeArr[pEmployeeManagment->employeeCount-1]=NULL; //last pointer in array points to null and free for reuse when adding an employee
}


int giveARaise(Employee* pEmployee,int newSalary){
    pEmployee->baseSalary=newSalary;
}

void printEmployeeManagement(const EmployeeManagment* pEmployeeManagment) {
    printf("Employee Management:\n");
    printf("====================\n");

    if (pEmployeeManagment == NULL) {
        printf("Employee manager is NULL\n");
        return;
    }

    if (pEmployeeManagment->employeeCount == 0) {
        printf("No employees found\n");
        return;
    }

    for (int i = 0; i < pEmployeeManagment->employeeCount; ++i) {
        printf("Employee %d:\n", i + 1);
        printEmployee(pEmployeeManagment->EmployeeArr[i]);
        printf("\n");
    }
}

void	freeEmployeeArr(Employee** EmployeeArr, int size)
{
    generalArrayFunction(*EmployeeArr, size, sizeof(Employee*), (void (*)(void *))freeEmployee);
    free(EmployeeArr);
}