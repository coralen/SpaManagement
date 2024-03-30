#ifndef _TREATMENT_MANAGER_H
#define _TREATMENT_MANAGER_H

#include "Treatment.h"
#include "List.h"

typedef struct {
	LIST treatments; // a struct needs to hold a linked list that holds a pointer to a struct as a void*
} TreatmentManager;

int initTreatmentManager(TreatmentManager* pTreatmentManager);
int initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int checkUniqeCode(char* code, TreatmentManager* pTreatmentManager);
int addTreatment(TreatmentManager* pTreatmentManager);
void deleteTreatment(TreatmentManager* pManager, Treatment* pTreatment);
void getTreatmentsWithCode(TreatmentManager* pManager, char* code);
int calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager);

#endif