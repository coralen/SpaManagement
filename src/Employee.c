#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Employee.h"


int initEmployee(Employee* pEmployee){ //add receiving the info from user
    char name[MAX_STRING];
    eEmployeeRole role= eNofRole;
    int seniority=0;
    int salary= MIN_WAGE;
    STATUS status= Available;

    getNameRoleSeniority(pEmployee, name, role, seniority);
    setSalary(pEmployee, salary);

}

int getNameRoleSeniority(Employee* pEmployee, char* name,eEmployeeRole role, int seniority){
    printf("Enter the first and last name of the new employee: \n");
    if (scanf("%s", name) != 1) {
        printf("Invalid input for name\n");
        return 0;
    }
    pEmployee->name = strdup(name);
    if (pEmployee->name == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    printf("Enter the role of the new employee, the options are: \n0- Receptionist\n1- Masseuse\n2- NailTechnician\n3- HotStonesTherapist\n4- Manager\n");
    int numRole;
    scanf("%d", &numRole);
    if (numRole >= 0 && numRole < eNofRole) {
        pEmployee->role = numRole;
        printf("Role set to: %s\n", EmployeeRole[pEmployee->role]);
    } else {
        printf("Invalid role number\n");
    }

    printf("Enter the numner of years that the employee has an experience for: \n");
    scanf("%d", &seniority);
    pEmployee->seniority=seniority;

    return 1;
}

int setSalary(Employee* pEmployee, int salary){
    printf("Currently, the salary is %d enter the new salary of the employee: \n",salary);
    scanf("%d", &salary);
    pEmployee->baseSalary=salary;
}

int changeStatus(Employee* pEmployee){
    if (pEmployee->status==Available)
        pEmployee->status=Busy;
    else pEmployee->status=Available;
}


void changeRole(Employee* pEmployee){
    printf("Role set to: %s\n", EmployeeRole[pEmployee->role]);
    printf("Enter the new role of the employee, the options are: \n0- Receptionist\n1- Masseuse\n2- NailTechnician\n3- HotStonesTherapist\n4- Manager\n");
    int numRole;
    scanf("%d", &numRole);
    if (numRole >= 0 && numRole < eNofRole) {
        pEmployee->role = numRole;
        printf("Role set to: %s\n", EmployeeRole[pEmployee->role]);
    } else {
        printf("Invalid role number\n");
    }
}
void printEmployee(const Employee* pEmployee) {
    if (pEmployee == NULL) {
        printf("Employee is NULL\n");
        return;
    }

    printf("Name: %s\n", pEmployee->name);
    printf("Base Salary: %d\n", pEmployee->baseSalary);
    printf("Seniority: %d\n", pEmployee->seniority);
    printf("Role: %s\n", EmployeeRole[pEmployee->role]);
    printf("Status: %s\n", pEmployee->status == Available ? "Busy" : "Available"  );
}



int freeEmployee(Employee* pEmployee) {
    if (pEmployee == NULL) {
        return 0; // Nothing to free if pEmployee is NULL
    }
    free(pEmployee->name);
    free(pEmployee);
    return 1;
}

