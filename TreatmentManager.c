#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "TreatmentManager.h"

int initTreatmentManager(TreatmentManager* pTreatmentManager)
{
	if (!L_init(&pTreatmentManager->treatmentArr)) return 0;
	pTreatmentManager->treatmentCount = 0;
	return 1;
}

int addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentArr.head)
	{
		freeTreatment(pTreatment);
		free(pTreatment);
		return 0;
	}

	NODE* ptr = &pTreatmentManager->treatmentArr.head;
	L_insert(ptr, pTreatment);

	return 1;
}

int deleteTreatmentFromList(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	const NODE* found = L_find(&pTreatmentManager->treatmentArr.head, pTreatment, compareTreatments);
	if (found)
	{
		NODE* nonConstFound = (NODE*)found;
		if (!L_delete_current(&pTreatmentManager->treatmentArr.head, nonConstFound, freeTreatmentWrapper)) return 0;
		return 1;
	}
	return 0;
}

int deleteTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	if (!deleteTreatmentFromList(pTreatment, pTreatmentManager)) return 0;
	pTreatmentManager->treatmentCount--;
	return 1;
}

void initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, Employee* pEmployee, Date* pDate)
{
	while (1)
	{
		getTreatmentCode(pTreatment->code);
		if (!findTreatmentWithCode(pTreatmentManager, pTreatment->code))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initTreatmentNoCode(pTreatment, option, pRoom, pEmployee, pDate);
}

Treatment* findTreatmentWithCode(TreatmentManager* pTreatmentManager, char* treatmentCode)
{
	NODE* ptr = &pTreatmentManager->treatmentArr.head;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		const char* currCode = ((Treatment*)ptr->key)->code;
		if (!strcmp(currCode, treatmentCode))
			return ptr->key;

		ptr = ptr->next;
	}
	return NULL;
}


int calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager)
{
	return 1;
}

int compareTreatments(const void* treatment1, const void* treatment2)
{
	const Treatment* treatmentA = (const Treatment*)treatment1;
	const Treatment* treatmentB = (const Treatment*)treatment2;
	return !(treatmentA == treatmentB);
}

void printTreatmentArrWithData(const TreatmentManager* pTreatmentManager)
{
	for (int i = 0; i < TREATMENT_TYPE_COUNT; i++)
	{
		printf("Treatment from type %s:\n", getTreatmentTypeString(i));
		printTreatmentHeaders();
		printArrByTreatmentType(pTreatmentManager, i);
	}
}

void printArrByTreatmentType(const TreatmentManager* pTreatmentManager, int type)
{
	switch (type)
	{
	case eMassage:
		printMassageHeaders();
		break;
	case eHotStones:
		printHotStonesHeaders();
		break;
	case eMeniPedi:
		printMenicurePedicureHeaders();
		break;
	}
	printf("\n");
	L_print_by_var(&pTreatmentManager->treatmentArr, (void (*)(const void*, int)) printTreatmentWithData, type);
}

void printTreatmentArr(const TreatmentManager* pTreatmentManager)
{
	printTreatmentHeaders();
	L_print(&pTreatmentManager->treatmentArr, (void (*)(const void*)) printTreatment);
}

int writeTreatmentManagerToBFile(FILE* pFile, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentArr.head) return 0;
	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	if (fwrite(&pTreatmentManager->treatmentCount, sizeof(int), 1, pFile) != 1) return 0;
	ptr = ptr->next;
	
	while (ptr) {
		if (!writeTreatmentToBFile(pFile, (Treatment*)ptr->key)) return 0;
		ptr = ptr->next;
	}
	return 1;
}

int readTreatmentManagerFromBFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
	if (!&pTreatmentManager->treatmentArr.head) return 0;
	if (fread(&pTreatmentManager->treatmentCount, sizeof(int), 1, pFile) != 1) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;
	Treatment* pTreatment = NULL;
	int count = pTreatmentManager->treatmentCount;

	while (count > 0)
	{
		if (!(pTreatment = (Treatment*)calloc(1, sizeof(Treatment)))) return 0;
		if (!readTreatmentFromBFile(pFile, pTreatment, pRoomManager, pEmployeeManager)) return 0;
		if (!L_insert(ptr, pTreatment)) return 0;
		ptr = ptr->next;
		count--;
	}
	return 1;
}

int writeTreatmentManagerToTextFile(FILE* pFile, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentArr.head) return 0;
	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	if (fprintf(pFile, "%d\n", pTreatmentManager->treatmentCount) < 0) return 0;
	ptr = ptr->next;
	while (ptr) {
		if (!writeTreatmentToTextFile(pFile, (Treatment*)ptr->key)) return 0;
		ptr = ptr->next;
	}
	return 1;
}

int readTreatmentManagerFromTextFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
	if (!&pTreatmentManager->treatmentArr.head) return 0;
	if (!fscanf(pFile, "%d\n", &pTreatmentManager->treatmentCount)) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;
	Treatment* pTreatment = NULL;
	int count = pTreatmentManager->treatmentCount;

	while (count > 0)
	{
		if (!(pTreatment = (Treatment*)calloc(1, sizeof(Treatment)))) return 0;
		if (!readTreatmentFromTextFile(pFile, pTreatment, pRoomManager, pEmployeeManager)) return 0;
		if (!L_insert(ptr, pTreatment)) return 0;
		ptr = ptr->next;
		count--;
	}
	return 1;
}

void updateTreatmenArrUtilitiesStatus(TreatmentManager* pTreatmentManager)
{
	L_func(&pTreatmentManager->treatmentArr, (void (*)(const void*)) updateTreatmentUtilitiesStatus);
}

int findTreatmentWithRoomAndDate(TreatmentManager* pTreatmentManager, Date* pDate, char* roomCode)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentArr.head) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	ptr = ptr->next;
	while (ptr) {
		if ((!strcmp(((Treatment*)ptr->key)->pTreatmentRoom->code, roomCode) && compareDates(&((Treatment*)ptr->key)->date, pDate))) return 1;
		ptr = ptr->next;
	}
	return 0;
}

Treatment* findTreatmentWithRoom(TreatmentManager* pTreatmentManager, char* roomCode)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentArr.head) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	ptr = ptr->next;
	while (ptr) {
		if ((!strcmp(((Treatment*)ptr->key)->pTreatmentRoom->code, roomCode))) return ptr->key;
		ptr = ptr->next;
	}
	return NULL;
}

int findTreatmentWithEmployeeAndDate(TreatmentManager* pTreatmentManager, Date* pDate, int employeeId)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentArr.head) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	ptr = ptr->next;
	while (ptr) {
		if (((((Treatment*)ptr->key)->pTreatmentEmployee->id == employeeId) && compareDates(&((Treatment*)ptr->key)->date, pDate))) return 1;
		ptr = ptr->next;
	}
	return 0;
}

Treatment* findTreatmentWithEmployee(TreatmentManager* pTreatmentManager, int employeeId)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentArr.head) return 0;

	NODE* ptr = &pTreatmentManager->treatmentArr.head;

	ptr = ptr->next;
	while (ptr) {
		if (((((Treatment*)ptr->key)->pTreatmentEmployee->id == employeeId))) return ptr->key;
		ptr = ptr->next;
	}
	return NULL;
}