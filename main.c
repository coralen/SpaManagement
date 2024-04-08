#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "Helper.h"
#include "SpaManager.h"
#include "EmployeeManager.h"

#define BIN_FILENAME "spa.bin"
#define TEXT_FILENAME "spa.txt"
#define BIN_C_FILENAME "spaC.bin"

typedef enum
{
	eAddRoom, eAddEmployee, eAddTreatment, ePrintRooms, ePrintEmployees, ePrintTreatments, ePrintSpa,
	eDeleteRoom, eDeleteEmployee, eDeleteTreatment,
	eGiveEmployeeARaise, eCalcSpaRevenue, eSortEmployees, eFindEmployee, eNofOptions
} eMenuOptions;

typedef enum { eTextFile, eBinFile, eManual, eNofLoadOptions } eLoadOptions;

const char* str[eNofOptions] = { "Add Room","Add Employee","Add Treatment", "Print rooms", "Print Employees",
								"Print treatments", "Print spa", "Delete room", "Delete employee", "Delete treatment",
								"Give employee a raise", "Calc the spa's revenue" , "Sort employees", "Find employee" };

const char* loadOptions[eNofLoadOptions] = { "From text file", "From binary file", "Enter manually" };

#define EXIT			-1

int menu();
void suggestLoadFromFile(SpaManager* pSpaManager);
void printLoadOptions();

int main()
{
	int option, stop = 0;
	SpaManager spaManager;
	
	printf("Hello and welcome to the Spa Management program!\n");
	suggestLoadFromFile(&spaManager);

	do {
		updateTreatmenArrUtilitiesStatus(&spaManager.treatmentManager);
		option = menu();

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

		case ePrintRooms:
			printRoomArr(&spaManager.roomManager);
			break;

		case ePrintEmployees:
			printEmployeeArr(&spaManager.employeeManager);
			break;

		case ePrintTreatments:
			printTreatmentListWithData(&spaManager.treatmentManager);
			break;

		case ePrintSpa:
			printSpa(&spaManager);
			break;

		case eDeleteRoom:
			deleteRoomFromSpa(&spaManager.roomManager, &spaManager.treatmentManager);
			break;

		case eDeleteEmployee:
			deleteEmployeeFromSpa(&spaManager.employeeManager, &spaManager.treatmentManager);
			break;

		case eDeleteTreatment:
			deleteTreatmentFromSpa(&spaManager.treatmentManager);
			break;

		case eGiveEmployeeARaise:
			giveEmployeeARaise(&spaManager.employeeManager);
			break;
		
		case eCalcSpaRevenue:
			calcSpaRevenue(&spaManager);
			break;

		case eSortEmployees:
			sortEmployees(&spaManager.employeeManager);
			break;

		case eFindEmployee:
			findEmployee(&spaManager.employeeManager);
			break;

		case EXIT:
			saveSpaToBFile(&spaManager, BIN_FILENAME, BIN_C_FILENAME);
			saveSpaToTextFile(&spaManager, TEXT_FILENAME);
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}

	} while (!stop);

	freeSpaManager(&spaManager);

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
	printf("Choose how to start the spa:\n");
	printLoadOptions();
	scanf("%d", &fileOption);
	while (getchar() != '\n');

	switch (fileOption) 
	{
	case 0:
		initSpaManagerFromTextFile(pSpaManager, TEXT_FILENAME);
		break;

	case 1:
		initSpaManagerFromBFile(pSpaManager, BIN_FILENAME, BIN_C_FILENAME);
		break;

	case 2:
		initSpaManager(pSpaManager);
		break;
	}
}

void printLoadOptions()
{
	for (int i = 0; i < eNofLoadOptions; i++)
		printf("%d - %s\n", i, loadOptions[i]);
}