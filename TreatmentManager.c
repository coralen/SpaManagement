#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstddef>

#include "TreatmentManager.h"


int initTreatmentManager(TreatmentManager* pTreatmentManager)
{
	if (!L_init(&pTreatmentManager->treatments)) return 0;
	return 1;
}

int addTreatment(TreatmentManager* pTreatmentManager)
{
	// check first if there are enought rooms and employees
	Treatment* pTreatment = (Treatment*)calloc(1, sizeof(Treatment));
	if (!pTreatment) return 0;

	initTreatment(pTreatment, pTreatmentManager);

	if (!&pTreatmentManager->treatments.head)
	{
		freeTreatment(pTreatment);
		free(pTreatment);
		return 0;
	}

	NODE* ptr = &pTreatmentManager->treatments.head;
	L_insert(ptr, pTreatment);

	return 1;
}

void deleteTreatment(Treatment* pTreatment)
{
	L_delete(pTreatment, freeTreatment);
}

void initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	while (1)
	{
		getTreatmentCode(pTreatment->code);
		if (checkUniqeTreatmentCode(pTreatment->code, pTreatmentManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initTreatmentNoCode(pTreatment);
}

int checkUniqeTreatmentCode(char* code, TreatmentManager* pTreatmentManager)
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

void getTreatmentsWithCode(TreatmentManager* pManager, char* code)
{

}

int calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager)
{
	return 1;
}