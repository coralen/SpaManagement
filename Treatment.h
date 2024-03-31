#ifndef _TREATMENT_H
#define _TREATMENT_H

#include "Helper.h"
#include "Date.h"
#include "Room.h"

#define TREATMENT_START_CHAR "T-"

typedef struct {
    char code[CODE];
    int duration; // according to type
    Date date;
    int price;
    Room* pTreatmentRoom; // need to add
    // union here all treatments (This is the inheritance part)
} Treatment;

int initTreatmentNoCode(Treatment* pTreatment);
void getTreatmentCode(char* code);
void getPrice(Treatment* pTreatment);
void describeTreatment(Treatment* pTreatment); // different implementation using union
void freeTreatment(Treatment* pTreatment);


#endif
