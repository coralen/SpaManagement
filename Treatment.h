#ifndef _TREATMENT_H
#define _TREATMENT_H

#include "Helper.h"
#include "Date.h"

typedef struct {
    char code[CODE]; // must
    int duration;
    Date date; // must
    int hour;
    int price;
    // union here all treatments (This is the inheritance part)
} Treatment;

void startTreatment(Treatment pTreatment, Date date, int hour);
void endTreatment(Treatment* pTreatment, Date date, int hour);
void describeTreatment(Treatment* pTreatment); // different implementation using union
void calculatePrice(Treatment pTreatment); // maybe in manager?


#endif
