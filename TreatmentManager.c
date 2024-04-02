#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int deleteTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	const NODE* found = L_find(&pTreatmentManager->treatments.head, pTreatment, compareTreatments);
	if (found)
	{
		NODE* nonConstFound = (NODE*)found; // L_delete can't work with CONST
		if (!L_delete(nonConstFound, freeTreatmentWrapper)) return 0;
		return 1;
	}
	return 0;
}

void initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, RoomType rType)
{
	while (1)
	{
		getTreatmentCode(pTreatment->code);
		if (getTreatmentWithCode(pTreatmentManager, pTreatment->code))
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

int compareTreatments(const void* treatment1, const void* treatment2)
{
	const Treatment* treatmentA = (const Treatment*)treatment1;
	const Treatment* treatmentB = (const Treatment*)treatment2;
	return !(treatmentA == treatmentB); // Return 0 if equal, non-zero otherwise
}