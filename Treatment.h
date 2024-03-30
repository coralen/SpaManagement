#ifndef _TREATMENT_H
#define _TREATMENT_H

#include "Helper.h"
#include "Date.h"
#include "Room.h"

typedef struct {
    char code[CODE];
    int duration; // delete?
    Date date;
    int price;
    Room* pTreatmentRoom;
    // union here all treatments (This is the inheritance part)
} Treatment;

int initTreatmentNoCode(Treatment* pTreatment);
void getTreatmentCode(char* code);
int isCodeValid(const char* code);
void getPrice(Treatment* pTreatment);
void describeTreatment(Treatment* pTreatment); // different implementation using union
void freeTreatment(Treatment* pTreatment);


#endif
