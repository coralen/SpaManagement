#define _CRT_SECURE_NO_WARNINGS
#include "TreatmentManager.h"
#include <cstddef>

int initTreatmentManager(TreatmentManager* pTreatmentManager)
{
	if (!L_init(&pTreatmentManager->treatments)) return 0;
	return 1;
}

int addTreatment(TreatmentManager* pTreatmentManager)
{
	Treatment* pTreatment = (Treatment*)calloc(1, sizeof(Treatment));
	if (!pTreatment) return 0;

	if (!initTreatment(pTreatment, pTreatmentManager))
	{
		freeTreatment(pTreatment);
		free(pTreatment);
		return 0;
	}

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

int initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager)
{
	while (1)
	{
		getTreatmentCode(pTreatment->code);
		if (checkUniqeCode(pTreatment->code, pTreatmentManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initTreatmentNoCode(pTreatment);
}

int checkUniqeCode(char* code, TreatmentManager* pTreatmentManager)
{
	NODE* ptr = &pTreatmentManager->treatments.head;
	while (ptr != NULL) {
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