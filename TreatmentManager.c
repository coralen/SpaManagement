#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstddef>
#include <stdlib.h>

#include "TreatmentManager.h"

int initTreatmentManager(TreatmentManager* pTreatmentManager)
{
	if (!L_init(&pTreatmentManager->treatments)) return 0;
	return 1;
}

int addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	if (!&pTreatmentManager->treatments.head)
	{
		freeTreatment(pTreatment);
		free(pTreatment);
		return 0;
	}

	NODE* ptr = &pTreatmentManager->treatments.head;
	L_insert(ptr, pTreatment);
	pTreatmentManager->roomCount++;

	return 1;
}

void deleteTreatment(Treatment* pTreatment)
{
	L_delete(pTreatment, freeTreatment);
}

void initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, RoomType rType)
{
	while (1)
	{
		getTreatmentCode(pTreatment->code);
		if (getTreatmentWithCode(pTreatment->code, pTreatmentManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initTreatmentNoCode(pTreatment, option, pRoom, rType);
}

Treatment* getTreatmentWithCode(TreatmentManager* pTreatmentManager, char* code)
{
	NODE* ptr = &pTreatmentManager->treatments.head;
	while (ptr != NULL)
	{
		if (((Treatment*)ptr->key)->code == code)
			return ptr->key;

		ptr = ptr->next;
	}
	return NULL;
}


int calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager)
{
	return 1;
}