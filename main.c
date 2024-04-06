#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "Helper.h"
#include "SpaManager.h"
#include "EmployeeManager.h"

#define BIN_FILENAME "spa.bin"
#define TEXT_FILENAME "spa.txt"

typedef enum
{
	eAddRoom, eAddEmployee, eAddTreatment, ePrintRoomsStatus, ePrintEmployees, ePrintTreatments, ePrintSpa,
	eCalcSpaRevenue, eSortEmployees, eFindTreatment, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Room","Add Employee","Add Treatment", "Print rooms", "Print Employees",
								"Print treatments", "Print spa",
								"Calc the spa's revenue" , "Sort employees", "Find treatment" };

#define EXIT			-1

int menu();
void suggestLoadFromFile(SpaManager* pSpaManager);

int main()
{
	int option, stop = 0;
	SpaManager spaManager;
	
	suggestLoadFromFile(&spaManager);

	do {
		option = menu();
		updateTreatmenArrUtilitiesStatus(&spaManager.treatmentManager);

		switch (option)
		{
		case eAddRoom:
			addRoom(&spaManager.roomManager);
			break;

		case eAddEmployee:
			addEmployee(&spaManager.employeeManager);
			break;

		case eAddTreatment:
			addTreatment(&spaManager.treatmentManager, &spaManager.roomManager, &spaManager.employeeManager);
			break;

		case ePrintRoomsStatus:
			printRoomArr(&spaManager.roomManager);
			break;

		case ePrintEmployees:
			printEmployeeArr(&spaManager.employeeManager);
			break;

		case ePrintTreatments:
			printTreatmentArrWithData(&spaManager.treatmentManager);
			break;

		case ePrintSpa:
			printSpa(&spaManager);
			break;

		case eCalcSpaRevenue:
			//calcSpaRevenue(); // implement
			break;

		case eSortEmployees:
			//sortEmployees(); // implement - Talya
			break;

		case eFindTreatment:
			//findTreatment(); // implement - Talya
			break;

		case EXIT:
			saveSpaToBFile(&spaManager, BIN_FILENAME);
			saveSpaToTextFile(&spaManager, TEXT_FILENAME);
			printf("Bye bye\n");
			getchar();
			getchar();
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

void suggestLoadFromFile(SpaManager* pSpaManager)
{
	int fileOption;
	printf("Do you want to load from file?\n0 - text\n1 - bin\n2 - No file\n");
	scanf("%d", &fileOption);
	while (getchar() != '\n');

	switch (fileOption) 
	{
	case 0:
		initManagerFromTextFile(pSpaManager, TEXT_FILENAME);
		break;

	case 1:
		initSpaManagerFromBFile(pSpaManager, BIN_FILENAME);
		break;

	case 2:
		initSpaManager(pSpaManager);
		break;
	}
}
