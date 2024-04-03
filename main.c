#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "Helper.h"
#include "SpaManagement.h"

typedef enum
{
	eAddRoom, eAddEmployee, eAddTreatment, ePrintTreatments, ePrintSpa, ePrintRoomsStatus,
	eCalcSpaRevenue, eSortEmployees, eFindTreatment, eNofOptions
} eMenuOptions;

// give a raise to an employee
// add treatment, ask if to set a treatment by seniority and role
// add a sync with clock before gettin room status
const char* str[eNofOptions] = { "Add Room","Add Employee","Add Treatment", "Print treatments",
								"Print Spa", "Print rooms status (up to date)",
								"Calc the spa's revenue" , "Sort employees", "Find treatment" };

#define EXIT			-1

int menu();

int main()
{
	int option, stop = 0;

	TreatmentManager tManager;
	RoomManager rManager;
	
	initTreatmentManagerAndRoomManager(&tManager, &rManager);

	do {
		option = menu();

		switch (option)
		{
		case eAddRoom:
			addRoom(&rManager);
			break;

		case eAddEmployee:
			//addEmployee(); // implement - Talya 
			break;

		case eAddTreatment:
			if (!addTreatment(&tManager, &rManager)) printf("Couldn't add treatment!");
			break;

		case ePrintTreatments:
			printf("in print treatments case\n");
			printTreatments(&tManager);
			break;

		case ePrintSpa:
			//printSpa(&tManager, &rManager); // implement
			break;

		case ePrintRoomsStatus:
			printRoomsStatus(&rManager); // implement
			break;

		case eCalcSpaRevenue:
			//calcSpaRevenue(); // implement
			break;

		case eSortEmployees:
			//sortEmployees(); // implement - Talya 
			break;

		case eFindTreatment:
			//findTreatment();
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}

	} while (!stop);

	//free(&tManager);
	//free(&rManager);

}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);

	char tav;
	scanf("%c", &tav);
	return option;
}