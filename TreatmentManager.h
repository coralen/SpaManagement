#ifndef _TREATMENT_MANAGER_H
#define _TREATMENT_MANAGER_H

#include "Treatment.h"
#include "List.h"

typedef struct {
	LIST treatments; // a struct needs to hold a linked list that holds a pointer to a struct as a void*
	int roomCount;
} TreatmentManager;

int			initTreatmentManager(TreatmentManager* pTreatmentManager);
int			addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int			calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager);
int			compareTreatments(const void* treatment1, const void* treatment2);
int			deleteTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
void		initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, RoomType rType);
Treatment*	getTreatmentWithCode(TreatmentManager* pTreatmentManager, char* code);


#endif