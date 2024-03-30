#ifndef _TREATMENT_MANAGER_H
#define _TREATMENT_MANAGER_H

#include "Treatment.h"

typedef struct {
	Treatment<LIST> treatments; // a struct needs to hold a linked list that holds a pointer to a struct as a void*
} TreatmentManager;

void addTreatment(TreatmentManager* pManager, Treatment* pTreatment);
void deleteTreatment(TreatmentManager* pManager, Treatment* pTreatment);
void getTreatmentsWithCode(TreatmentManager* pManager, char* code);

#endif