#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "headers/Helper.h"
#include "SpaManagement.h"
#include "TreatmentManager.h"
#include "RoomManager.h"
#include "EmployeeManagment.h"

#define FF 5 //TODO: what is this for?
int main() {
    EmployeeManagment employeeManagment;
//    SpaManagment spa;
//    TreatmentManager treatmentM;

    initEmployeeManagment(&employeeManagment);
//    initSpaManagment(&spa);
//    initTreatmentManager(&treatmentM);


    addEmployee(&employeeManagment);
    addEmployee(&employeeManagment);
    printEmployeeManagement( &employeeManagment);

    giveARaise(employeeManagment.EmployeeArr[0],35);
    printEmployeeManagement( &employeeManagment);

//   if( !isEmployeeAvailable(employeeManagment.EmployeeArr[0])) printf("available"); else printf("unavailable\n");
//   printf("employee by role:\n");
//   findEmployeeByRole(&employeeManagment,  2);
//    printf("\nemployee by seniority and role:\n");
//   findEmployeeBySeniorityAndRole(&employeeManagment,  1, 1);

   // changeRole(employeeManagment.EmployeeArr[0]);
    //changeStatus(employeeManagment.EmployeeArr[0]);

//    startTreatment(&spa);
 //   deleteEmployee(&employeeManagment, "name");
  //  printEmployeeManagement( &employeeManagment);
}


//
//typedef enum
//{
//    eAddTreatment,eAddEmployee, eAddRoom, ePrintSpa, ePrintTreatments, ePrintEmployees, eNofOptions
//} eMenuOptions;
//
//const char* str[eNofOptions] = { "Add Treatment","Add Employee","Add Room",
//                                 "Print Spa", "Print Treatments",
//                                 "Print Employees" };
//
//#define EXIT	-1
//int menu();
//
//int main()
//{
//    EmployeeManagment	employeeManagment;
//    SpaManagment	spa;
//    TreatmentManager treatmentM;
//
//    initEmployeeManagment(&employeeManagment);
//    initSpaManagment(&spa);
//    initTreatmentManager(&treatmentM);
//
//    int option;
//    int stop = 0;
//
//
//    do
//    {
//        option = menu();
//        switch (option)
//        {
//            case eAddTreatment:
//                if (!startTreatment())//coral add here
//                    printf("Error adding plane\n");
//                break;
//
//            case eAddEmployee:
//                if (!addEmployee(&employeeManagment))
//                    printf("Error adding airport\n");
//                break;
//
////            case eAddRoom://coral change this
////                if (!AddRoom(&company, &manager))
////                    printf("Error adding flight\n");
////                break;
////
////            case ePrintSpa:// will be finished later
////                printCompany(&company);
////                break;
////
////            case ePrintTreatments:// will be finished later
////                printAirports(&manager);
////                break;
////
////            case ePrintEmployees:// will be finished later
////                doPrintFlightsWithPlaneType(&company);
////                break;
//
//            case EXIT:
//                printf("Bye bye\n");
//                stop = 1;
//                break;
//
//            default:
//                printf("Wrong option\n");
//                break;
//        }
//    } while (!stop);
////
////    freeManager(&manager);
////    freeCompany(&company);
//
//    return 1;
//}
//
//int menu()
//{
//    int option;
//    printf("\n\n");
//    printf("Please choose one of the following options\n");
//    for(int i = 0 ; i < eNofOptions ; i++)
//        printf("%d - %s\n",i,str[i]);
//    printf("%d - Quit\n", EXIT);
//    scanf("%d", &option);
//    //clean buffer
//    char tav;
//    scanf("%c", &tav);
//    return option;
//}