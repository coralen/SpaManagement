#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SpaManagement.h"

int initSpaManagment(SpaManagment* eSpa){
    char name[MAX_STRING];
    char location[MAX_STRING];

    EmployeeManagment* eManager;
    initEmployeeManagment(eManager);
  //  TreatmentManager tManager;
 //   initTreatmentManager(&tManager);
 //   RoomManager rManger;
//    initRoomManager(&rManger);

}

void startTreatment(SpaManagment* eSpa){
    //ask for the type of treatment

   // getRoom() - get the appropriete room for the kind of treatment
   int role; //role is set according to the type of treatment since role is the job of the employee
   getEmployee(eSpa->eManager, role);


}

int getEmployee(EmployeeManagment* eManager, int role){
    printf("Do you want to choose an employee by seniority? \n0- no \n1- yes\n");
    int choise;
    scanf("%d", &choise);
    if (choise==0){
        findEmployeeByRole(eManager, role);
    }else if (choise ==1){
        printf("What seniority do you want?\n");
        int seniority;
        scanf("%d", &seniority);
        findEmployeeBySeniorityAndRole(eManager,seniority, role);
    } else printf("choise is invalid");
}

void endTreatment(Treatment* pTreatment, Date date, int hour);
int calcRevenue();
int writeToText();
int writeToFile();
int readFromTextFile();
int readFromBinaryFile();