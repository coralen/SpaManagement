#ifndef _TREATMENT_H
#define _TREATMENT_H

#include "Helper.h"
#include "Date.h"
#include "Room.h"

#include "Massage.h"
#include "HotStones.h"
#include "MeniPedi.h"

#define TREATMENT_START_CHARS "T-"
#define TREATMENT_TYPE_COUNT 3

static const char* treatmentTypeString[TREATMENT_TYPE_COUNT] = { "Massage", "Hot Stones" ,"Meni Pedi" };
static const int treatmentDurationInt[TREATMENT_TYPE_COUNT] = { 45, 30 , 60 };
static const int treatmentPriceInt[TREATMENT_TYPE_COUNT] = { 300, 250, 100 };

typedef enum { MASSAGE, HOT_STONES, MENI_PEDI } TreatmentType;

typedef union {
    Massage massage;
    HotStones hotStones;
    MeniPedi meniPedi;
} TreatmentData;

typedef struct {
    char code[CODE];
    Date date;
    int duration;
    int price;
    Room* pTreatmentRoom;
    TreatmentType type;
    TreatmentData data;
} Treatment;

int     initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, RoomType rType);
int     initMassage(Treatment* pTreatment, Room* pRoom, RoomType rType);
void    getTreatmentCode(char* code);
void    initHotStones(Treatment* pTreatment, Room* pRoom, RoomType rType);
void    initMeniPedi(Treatment* pTreatment, Room* pRoom, RoomType rType);
void    describeTreatment(Treatment* pTreatment); // different implementation using union
void    freeTreatment(Treatment* pTreatment);
void    printTreatmentTypes();


#endif
