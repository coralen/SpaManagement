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
	if (!L_init(&pTreatmentManager->treatmentList)) return 0;
	pTreatmentManager->treatmentCount = 0;
	return 1;
}

int addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentList.head)
	{
		freeTreatment(pTreatment);
		free(pTreatment);
		return 0;
	}
	NODE* ptr;

	if (!pTreatmentManager->treatmentCount) 
		ptr = &pTreatmentManager->treatmentList.head;
	else 
		ptr = findInsertionPoint(pTreatmentManager, pTreatment);
	if (!L_insert(ptr, pTreatment)) 
	{
		freeTreatment(pTreatment);
		return 0;
	}

	return 1;
}

NODE* findInsertionPoint(TreatmentManager* pTreatmentManager, Treatment* pNewTreatment) 
{
	NODE* current = &pTreatmentManager->treatmentList.head;
	current = current->next;
	NODE* previous = &pTreatmentManager->treatmentList.head;

	while (current != NULL) 
	{
		Treatment* currentTreatment = (Treatment*)(current->key);
		if (compareDates(&pNewTreatment->date, &currentTreatment->date) < 0) {
			break;
		}
		previous = current;
		current = current->next;
	}

	return previous;

}

int deleteTreatmentFromList(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	const NODE* found = L_find(&pTreatmentManager->treatmentList.head, pTreatment, compareTreatments);
	if (found)
	{
		NODE* nonConstFound = (NODE*)found;
		if (!L_delete_current(&pTreatmentManager->treatmentList.head, nonConstFound, freeTreatmentWrapper)) return 0;
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

Treatment* findTreatmentWithCode(const TreatmentManager* pTreatmentManager, const char* treatmentCode)
{
	TreatmentManager tmpTreatmentManager = *pTreatmentManager;
	NODE* ptr = &tmpTreatmentManager.treatmentList.head;
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


int revenueFromTreatments(TreatmentManager* pTreatmentManager)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	int revenu = 0;

	NODE* ptr = &pTreatmentManager->treatmentList.head;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		revenu += ((Treatment*)ptr->key)->price;
		ptr = ptr->next;
	}
	return revenu;
}

int paymentForEmployees(TreatmentManager* pTreatmentManager)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	int payment = 0;

	NODE* ptr = &pTreatmentManager->treatmentList.head;
	ptr = ptr->next;
	while (ptr != NULL)
	{
		payment += ((Treatment*)ptr->key)->pTreatmentEmployee->salary;
		ptr = ptr->next;
	}
	return payment;
}

int compareTreatments(const void* treatment1, const void* treatment2)
{
	const Treatment* treatmentA = (const Treatment*)treatment1;
	const Treatment* treatmentB = (const Treatment*)treatment2;
	return !(treatmentA == treatmentB);
}

void printTreatmentListWithData(const TreatmentManager* pTreatmentManager)
{
	if (!pTreatmentManager->treatmentCount)
	{
		printf("The spa has no treatments\n");
		return;
	}
	for (int i = 0; i < eNofTreatmentType; i++)
	{
		printf("Treatment from type %s:\n", getTreatmentTypeString(i));
		printTreatmentHeaders();
		printArrByTreatmentType(pTreatmentManager, i);
	}
}

void printArrByTreatmentType(const TreatmentManager* pTreatmentManager, int type)
{
	TREATMENT_TYPE_SWITCH_CASE(type, printMassageHeaders, NULL, printHotStonesHeaders, NULL, printMenicurePedicureHeaders, NULL);
	L_print_by_var(&pTreatmentManager->treatmentList, (void (*)(const void*, int)) printTreatmentWithData, type);
}

void printTreatmentList(const TreatmentManager* pTreatmentManager)
{
	printTreatmentHeaders();
	L_print(&pTreatmentManager->treatmentList, (void (*)(const void*)) printTreatment);
}

int writeTreatmentManagerToBFile(FILE* pFile, FILE* pCFile, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentList.head) return 0;
	NODE* ptr = &pTreatmentManager->treatmentList.head;
	if (fwrite(&pTreatmentManager->treatmentCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!pTreatmentManager->treatmentCount) return 1;

	ptr = ptr->next;
	
	while (ptr) {
		if (!writeTreatmentToBFile(pFile, pCFile, (Treatment*)ptr->key)) return 0;
		ptr = ptr->next;
	}
	return 1;
}

int readTreatmentManagerFromBFile(FILE* pFile, FILE* pCFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
	if (!&pTreatmentManager->treatmentList.head) return 0;
	if (fread(&pTreatmentManager->treatmentCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!pTreatmentManager->treatmentCount) return 1;

	Treatment* pTreatment = NULL;
	int count = pTreatmentManager->treatmentCount;

	while (count > 0)
	{
		if (!(pTreatment = (Treatment*)calloc(1, sizeof(Treatment)))) return 0;
		if (!readTreatmentFromBFile(pFile, pCFile, pTreatment, pRoomManager, pEmployeeManager)) return 0;
		if (!addTreatmentToList(pTreatment, pTreatmentManager)) return 0;
		count--;
	}
	return 1;
}

int writeTreatmentManagerToTextFile(FILE* pFile, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatmentList.head) return 0;
	NODE* ptr = &pTreatmentManager->treatmentList.head;

	if (fprintf(pFile, "%d\n", pTreatmentManager->treatmentCount) < 0) return 0;
	if (!pTreatmentManager->treatmentCount) return 1;
	ptr = ptr->next;
	while (ptr) {
		if (!writeTreatmentToTextFile(pFile, (Treatment*)ptr->key)) return 0;
		ptr = ptr->next;
	}
	return 1;
}

int readTreatmentManagerFromTextFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager)
{
	if (!&pTreatmentManager->treatmentList.head) return 0;
	if (!fscanf(pFile, "%d\n", &pTreatmentManager->treatmentCount)) return 0;
	if (!pTreatmentManager->treatmentCount) return 1;

	Treatment* pTreatment = NULL;
	int count = pTreatmentManager->treatmentCount;

	while (count > 0)
	{
		if (!(pTreatment = (Treatment*)calloc(1, sizeof(Treatment)))) return 0;
		if (!readTreatmentFromTextFile(pFile, pTreatment, pRoomManager, pEmployeeManager)) return 0;
		if (!addTreatmentToList(pTreatment, pTreatmentManager)) return 0;
		count--;
	}
	return 1;
}

void updateTreatmenArrUtilitiesStatus(TreatmentManager* pTreatmentManager)
{
	L_func(&pTreatmentManager->treatmentList, (void (*)(const void*)) updateTreatmentUtilitiesStatus);
}

int findTreatmentWithRoomAndDate(const TreatmentManager* pTreatmentManager, const Date* pDate, const char* roomCode)
{
	TreatmentManager tmpTreatmentManager = *pTreatmentManager;
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentList.head) return 0;

	NODE* ptr = &tmpTreatmentManager.treatmentList.head;

	ptr = ptr->next;
	while (ptr) {
		if ((!strcmp(((Treatment*)ptr->key)->pTreatmentRoom->code, roomCode) && !compareDates(&((Treatment*)ptr->key)->date, pDate))) return 1;
		ptr = ptr->next;
	}
	return 0;
}

Treatment* findTreatmentWithRoom(const TreatmentManager* pTreatmentManager, const char* roomCode)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentList.head) return 0;

	TreatmentManager tmpTreatmentManager = *pTreatmentManager;
	NODE* ptr = &tmpTreatmentManager.treatmentList.head;

	ptr = ptr->next;
	while (ptr) {
		if ((!strcmp(((Treatment*)ptr->key)->pTreatmentRoom->code, roomCode))) return ptr->key;
		ptr = ptr->next;
	}
	return NULL;
}

int findTreatmentWithEmployeeAndDate(const TreatmentManager* pTreatmentManager, const Date* pDate, const int employeeId)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentList.head) return 0;

	TreatmentManager tmpTreatmentManager = *pTreatmentManager;
	NODE* ptr = &tmpTreatmentManager.treatmentList.head;

	ptr = ptr->next;
	while (ptr) {
		if (((((Treatment*)ptr->key)->pTreatmentEmployee->id == employeeId) && !compareDates(&((Treatment*)ptr->key)->date, pDate))) return 1;
		ptr = ptr->next;
	}
	return 0;
}

Treatment* findTreatmentWithEmployee(const TreatmentManager* pTreatmentManager, const int employeeId)
{
	if (!pTreatmentManager->treatmentCount) return 0;
	if (!&pTreatmentManager->treatmentList.head) return 0;

	TreatmentManager tmpTreatmentManager = *pTreatmentManager;
	NODE* ptr = &tmpTreatmentManager.treatmentList.head;

	ptr = ptr->next;
	while (ptr) {
		if (((((Treatment*)ptr->key)->pTreatmentEmployee->id == employeeId))) return ptr->key;
		ptr = ptr->next;
	}
	return NULL;
}

void freeTreatmentManager(TreatmentManager* pTreatmentManager)
{
	CHECK_NULL(pTreatmentManager);
	L_func(&pTreatmentManager->treatmentList, (void (*)(const void*))freeTreatmentWrapper);
}