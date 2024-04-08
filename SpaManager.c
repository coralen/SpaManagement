#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/SpaManager.h"

const char* overdraftOptionsString[eNoOfOverdraftOptions] = { "Increase budget", "Fire an employee", "Delete treatment", "Stay in overdraft" };

int initManagers(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
	if (!initTreatmentManager(pTreatmentManager)) return 0;
	initRoomManager(pRoomManager);
	initEmployeeManager(pEmployeeManager);
	return 1;
}

int initSpaManager(SpaManager* pSpa)
{
	if (!setSpaName(&pSpa->name)) return 0;
	if (!setSpaLocation(&pSpa->location)) return 0;
	setSpaBudget(pSpa);
	initManagers(&pSpa->treatmentManager, &pSpa->roomManager, &pSpa->employeeManager);
	return 1;
}

int initSpaManagerFromBFile(SpaManager* pSpaManager, const char* fileName, const char* cFileName)
{
	setSpaDefaults(pSpaManager);
	FILE* pFile = fopen(fileName, "rb");
	FILE* cFile = fopen(cFileName, "rb");
	if (!pFile) return 0;
	if (!cFile) return 0;
	if (!readSpaFromBFile(pFile, cFile, pSpaManager)) return 0;
	fclose(pFile);
	fclose(cFile);
	return 1;
}

int initSpaManagerFromTextFile(SpaManager* pSpaManager, const char* fileName)
{
	setSpaDefaults(pSpaManager);
	FILE* pFile = fopen(fileName, "r");
	if (!pFile) return 0;
	if (!readSpaFromTextFile(pFile, pSpaManager)) return 0;
	fclose(pFile);
	return 1;
}

void setSpaDefaults(SpaManager* pSpaManager)
{
	pSpaManager->budget = 0;
	initRoomManager(&pSpaManager->roomManager);
	initEmployeeManager(&pSpaManager->employeeManager);
	initTreatmentManager(&pSpaManager->treatmentManager);
}

int setSpaName(char** name)
{
	char inputName[MAX_STRING];

	printf("Please enter your Spa's name: \n");
	scanf(SCANF_FORMAT, inputName);
	while (getchar() != '\n');
	if (!(*name = (char*)malloc((strlen(inputName) + 1) * sizeof(char)))) return 0;
	strcpy(*name, inputName);
	capitalFirst(*name);

	return 1;
}

int setSpaLocation(char** location)
{
	char inputLocation[MAX_STRING];

	printf("And what is the location of ypur Spa? \n");
	scanf(SCANF_FORMAT, inputLocation);
	while (getchar() != '\n');

	if (!(*location = (char*)malloc((strlen(inputLocation) + 1) * sizeof(char)))) return 0;
	strcpy(*location, inputLocation);
	capitalFirst(*location);

	return 1;
}

void setSpaBudget(SpaManager* pSpaManager)
{
	printf("Enter the budget for the spa: ");
	scanf("%d", &pSpaManager->budget);
}

void increaseSpaBudget(SpaManager* pSpaManager)
{
	int addBudget;
	printf("Enter the amount to add to the budget: \n");
	scanf("%d", &addBudget);
	pSpaManager->budget = pSpaManager->budget + addBudget;
}

int addTreatment(TreatmentManager* pTreatmentManager, const RoomManager* pRoomManager, const EmployeeManager* pEmployeeManager)
{
	if (!checkRequirments(pTreatmentManager, pRoomManager, pEmployeeManager)) return 0;

	int option, validFlag = 0;
	RoomType rType = (RoomType)0;
	eEmployeeRole eRole = (eEmployeeRole)0;
	Room* pRoom;
	Employee* pEmployee;

	Date date;

	getCorrectDate(&date);
	getCorrentHour(&date);
	if (!isDateRelevant(&date))
	{
		printf("The date is not up to date!");
		return 0;
	}

	do {
		printf("Please choose the type of treatment:\n");
		printTreatmentTypes();
		scanf("%d", &option);
		while (getchar() != '\n');
		if (option > -1 && option < eNofTreatmentType) validFlag = 1;
		else printf("Invalid choice, try again\n");
	} while (!validFlag);

	switch (option)
	{
	case eMassage:
		rType = (RoomType)MASSAGE_ROOM_TYPE;
		eRole = (eEmployeeRole)MASSAGE_EMPLOYEE_ROLE;
		break;

	case eHotStones:
		rType = (RoomType)HOT_STONES_ROOM_TYPE;
		eRole = (eEmployeeRole)HOT_STONES_EMPLOYEE_ROLE;
		break;

	case eMeniPedi:
		rType = (RoomType)MENI_PEDI_ROOM_TYPE;
		eRole = (eEmployeeRole)MENI_PEDI_EMPLOYEE_ROLE;
		break;
	}

	pRoom = findAvailableRoom(pRoomManager, pTreatmentManager, rType, &date);
	if (!pRoom)
	{
		printf("No available room for this treatment\n");
		return 0;
	}

	pEmployee = findAvailableEmployee(pEmployeeManager, pTreatmentManager, eRole, &date);
	if (!pEmployee)
	{
		printf("No available employee for this treatment\n");
		return 0;
	}

	Treatment* pTreatment = (Treatment*)calloc(1, sizeof(Treatment));
	if (!pTreatment) return 0;

	initTreatment(pTreatment, pTreatmentManager, option, pRoom, pEmployee, &date);
	if (!addTreatmentToList(pTreatment, pTreatmentManager)) return 0;
	pTreatmentManager->treatmentCount++;
	return 1;

}

int	checkRequirments(const TreatmentManager* pTreatmentManager, const RoomManager* pRoomManager, const EmployeeManager* pEmployeeManager)
{
	if (!pRoomManager->roomCount)
	{
		printf("Not enough rooms to add a new treatment!\n");
		return 0;
	}

	if (!pEmployeeManager->employeeCount)
	{
		printf("Not enough employees to add a new treatment!\n");
		return 0;
	}

	return 1;
}

const char* getOverdraftOptionsString(const int optionNum)
{
	return overdraftOptionsString[optionNum];
}

void printOverdraftOptions()
{
	for (int i = 0; i < eNoOfOverdraftOptions; i++)
		printf("%d - %s\n", i, getOverdraftOptionsString(i));
}

void printSpa(const SpaManager* pSpaManager)
{
	printf("Spa information:\n================\n");
	printf("Name: %s\nLocation: %s\nBudget: %d\n\n", pSpaManager->name, pSpaManager->location, pSpaManager->budget);

	if (!pSpaManager->roomManager.roomCount) printf("The spa has no rooms\n");
	else {
		printf("There are %d rooms: \n", pSpaManager->roomManager.roomCount);
		printRoomArr(&pSpaManager->roomManager);
		printf("\n");
	}

	if (!pSpaManager->employeeManager.employeeCount) printf("The spa has no employees\n");
	else {
		printf("There are %d employees: \n", pSpaManager->employeeManager.employeeCount);
		printEmployeeArr(&pSpaManager->employeeManager);
		printf("\n");
	}

	if (!pSpaManager->treatmentManager.treatmentCount) printf("The spa has no treatments\n");
	else {
		printf("There are %d treatments: \n", pSpaManager->treatmentManager.treatmentCount);
		printTreatmentList(&pSpaManager->treatmentManager);
		printf("\n");
	}

}

void calcSpaRevenue(SpaManager* pSpaManager)
{
	int revenue, tRevenue, tPayment, option;

	tRevenue = revenueFromTreatments(&pSpaManager->treatmentManager);
	tPayment = paymentForEmployees(&pSpaManager->treatmentManager);
	revenue = (pSpaManager->budget + tRevenue) - tPayment;

	printf("Total revenue of the spa is: %d\n", revenue);
	printf("Revenue from treatments: %d\n", tRevenue);
	printf("Payments for employees (for treatments): %d\n", tPayment);
	printf("\n");

	if (revenue < 0)
	{
		printf("You are in OVERDRAFT in the bank!\nChoose one of the next options:\n");
		printOverdraftOptions();
		scanf("%d", &option);
		while (getchar() != '\n');
		switch (option)
		{
		case eIncreaseBudget:
			increaseSpaBudget(pSpaManager);
			break;
		case eFireEmployee:
			deleteEmployeeFromSpa(&pSpaManager->employeeManager, &pSpaManager->treatmentManager);
			break;
		case eDeleteTreatmant:
			deleteTreatmentFromSpa(&pSpaManager->treatmentManager);
			break;
		case eStayInOverdraft:
			break;
		}
	}
}


int saveSpaToBFile(const SpaManager* pSpaManager, const char* fileName, const char* cFileName)
{
	FILE* pFile;
	FILE* pCFile;
	pFile = fopen(fileName, "wb");
	pCFile = fopen(cFileName, "wb");
	if (!pFile) return 0;
	if (!pCFile) return 0;
	if (!writeSpaToBFile(pFile, pCFile, pSpaManager)) return 0;
	fclose(pFile);
	fclose(pCFile);

	return 1;
}

int writeSpaToBFile(FILE* pFile, FILE* pCFile, const SpaManager* pSpaManager)
{
	int len;
	TreatmentManager treatmentManager = pSpaManager->treatmentManager;

	len = (int)(strlen(pSpaManager->name) + 1);
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pSpaManager->name, sizeof(char), len, pFile) != len) return 0;

	len = (int)(strlen(pSpaManager->location) + 1);
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pSpaManager->location, sizeof(char), len, pFile) != len) return 0;

	if (fwrite(&pSpaManager->budget, sizeof(int), 1, pFile) != 1) return 0;

	if (!writeRoomManagerToBFile(pFile, &pSpaManager->roomManager)) return 0;
	if (!writeEmployeeManagerToBFile(pFile, &pSpaManager->employeeManager)) return 0;
	if (!writeTreatmentManagerToBFile(pFile, pCFile , &treatmentManager)) return 0;

	return 1;

}

int readSpaFromBFile(FILE* pFile, FILE* pCFile, SpaManager* pSpaManager)
{
	int len;

	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (!(pSpaManager->name = (char*)malloc(len * sizeof(char)))) return 0;
	if (fread(pSpaManager->name, sizeof(char), len, pFile) != len) return 0;

	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (!(pSpaManager->location = (char*)malloc(len * sizeof(char)))) return 0;
	if (fread(pSpaManager->location, sizeof(char), len, pFile) != len) return 0;

	if (fread(&pSpaManager->budget, sizeof(int), 1, pFile) != 1) return 0;

	if (!readRoomManagerFromBFile(pFile, &pSpaManager->roomManager)) return 0;
	if (!readEmployeeManagerFromBFile(pFile, &pSpaManager->employeeManager)) return 0;
	if (!readTreatmentManagerFromBFile(pFile, pCFile, &pSpaManager->treatmentManager, &pSpaManager->roomManager, &pSpaManager->employeeManager)) return 0;

	return 1;
}

int saveSpaToTextFile(const SpaManager* pSpaManager, const char* fileName)
{
	FILE* pFile;
	pFile = fopen(fileName, "w");
	if (!pFile) return 0;
	if (!writeSpaToTextFile(pFile, pSpaManager)) return 0;
	fclose(pFile);

	return 1;
}

int writeSpaToTextFile(FILE* pFile, const SpaManager* pSpaManager)
{
	TreatmentManager treatmentManager = pSpaManager->treatmentManager;
	if (fprintf(pFile, "%s\n", pSpaManager->name) < 0) return 0;
	if (fprintf(pFile, "%s\n", pSpaManager->location) < 0) return 0;
	if (fprintf(pFile, "%d\n", pSpaManager->budget) < 0) return 0;

	if (!writeRoomManagerToTextFile(pFile, &pSpaManager->roomManager)) return 0;
	if (!writeEmployeeManagerToTextFile(pFile, &pSpaManager->employeeManager)) return 0;
	if (!writeTreatmentManagerToTextFile(pFile, &treatmentManager)) return 0;
	
	return 1;
}

int readSpaFromTextFile(FILE* pFile, SpaManager* pSpaManager)
{
	char tmp[MAX_STRING] = { 0 };

	if (!fscanf(pFile, " %[^\n]\n", tmp)) return 0;
	pSpaManager->name = strdup(tmp);

	if (!fscanf(pFile, " %[^\n]\n", tmp)) return 0;
	pSpaManager->location = strdup(tmp);

	if (!fscanf(pFile, "%d\n", &pSpaManager->budget)) return 0;
	if (!readRoomManagerFromTextFile(pFile, &pSpaManager->roomManager)) return 0;
	if (!readEmployeeManagerFromTextFile(pFile, &pSpaManager->employeeManager)) return 0;
	if (!readTreatmentManagerFromTextFile(pFile, &pSpaManager->treatmentManager, &pSpaManager->roomManager, &pSpaManager->employeeManager)) return 0;
	
	return 1;
}


Room* findAvailableRoom(const RoomManager* pRoomManager, const TreatmentManager* pTreatmentManager, const RoomType type, const Date* pDate)
{
	for (int i = 0; i < pRoomManager->roomCount; i++)
		if (pRoomManager->roomArr[i].type == type && !findTreatmentWithRoomAndDate(pTreatmentManager, pDate, pRoomManager->roomArr[i].code))
			return &pRoomManager->roomArr[i];

	return NULL;
}

Employee* findAvailableEmployee(const EmployeeManager* pEmployeeManager, const TreatmentManager* pTreatmentManager, const eEmployeeRole role, const Date* pDate)
{
	for (int i = 0; i < pEmployeeManager->employeeCount; i++)
		if (pEmployeeManager->EmployeeArr[i]->role == role && !findTreatmentWithEmployeeAndDate(pTreatmentManager, pDate, pEmployeeManager->EmployeeArr[i]->id))
			return pEmployeeManager->EmployeeArr[i];

	return NULL;
}

int deleteRoomFromSpa(RoomManager* pRoomManager, const TreatmentManager* pTreatmentManager)
{
	if (!pRoomManager->roomCount)
	{
		printf("No rooms are available\n");
		return 0;
	}

	char tmpCode[TOTAL_CODE + 1];
	int validFlag = 0;
	Room* pRoom;
	Treatment* pTreatment;

	printf("Please choose code of an available room:\n");
	printRoomArr(pRoomManager);
	while (!validFlag)
	{
		setRoomCode(tmpCode);
		if (!(pRoom = findRoomByCode(pRoomManager, tmpCode))) "No room with this code! try again\n";
		else
		{
			if ((pTreatment = findTreatmentWithRoom(pTreatmentManager, tmpCode)))
			{
				printf("This room is booked by treatment with code %s.\nDelete the treatment first\n", pTreatment->code);
				return 0;
			}
			else
			{
				deleteRoom(pRoom, pRoomManager);
				validFlag = 1;
			}
		}
	}

	return 1;
}

int deleteEmployeeFromSpa(EmployeeManager* pEmployeeManager, const TreatmentManager* pTreatmentManager)
{
	if (!pEmployeeManager->employeeCount)
	{
		printf("No employees are available\n");
		return 0;
	}

	int tmpId;
	int validFlag = 0;
	Employee* pEmployee;
	Treatment* pTreatment;

	printf("Please choose id of an available employee:\n");
	printEmployeeArr(pEmployeeManager);
	while (!validFlag)
	{
		scanf("%d", &tmpId);
		if (!(pEmployee = findEmployeeById(pEmployeeManager, tmpId))) printf("No employee with this id! try again\n");
		else {
			if ((pTreatment = findTreatmentWithEmployee(pTreatmentManager, tmpId)))
			{
				printf("This employee is booked by treatment with code %s.\nDelete the treatment first\n", pTreatment->code);
				return 0;
			}
			else
			{
				deleteEmployee(pEmployeeManager, pEmployee->name);
				validFlag = 1;
			}
		}
	}
	return 1;
}

int deleteTreatmentFromSpa(TreatmentManager* pTreatmentManager)
{
	if (!pTreatmentManager->treatmentCount)
	{
		printf("No treatments are available\n");
		return 0;
	}

	char tmpCode[TOTAL_CODE + 1];
	int validFlag = 0;
	Treatment* pTreatment;

	printf("Please choose code of an available treatment:\n");
	printTreatmentList(pTreatmentManager);
	while (!validFlag)
	{
		getTreatmentCode(tmpCode);
		if (!(pTreatment = findTreatmentWithCode(pTreatmentManager, tmpCode))) "No treatment with this code! try again\n";
		else {
			if (pTreatment->isActive)
			{
				printf("This treatment is in active! please wait for it to be done\n");
				return 0;
			}
			else
			{
				deleteTreatment(pTreatment, pTreatmentManager);
				validFlag = 1;
			}

		}
	}
	return 1;
}

void freeSpaManager(SpaManager* pSpaManager)
{
	CHECK_NULL(pSpaManager);
	free(pSpaManager->name);
	free(pSpaManager->location);

	freeRoomManager(&pSpaManager->roomManager);
	freeEmployeeManager(&pSpaManager->employeeManager);
	freeTreatmentManager(&pSpaManager->treatmentManager);
}