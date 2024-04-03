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


typedef enum { MASSAGE, HOT_STONES, MENI_PEDI } TreatmentType;

typedef union {
    Massage massage;
    HotStones hotStones;
    MeniPedi meniPedi;
} TreatmentData;

typedef struct {
    char code[TOTAL_CODE + 1];
    Date date;
    int duration;
    int price;
    Room* pTreatmentRoom;
    TreatmentType type;
    TreatmentData data;
} Treatment;

int         initTreatmentNoCode(Treatment* pTreatment, int option, Room* pRoom, RoomType rType);
int         initMassage(Treatment* pTreatment, Room* pRoom, RoomType rType);
void        getTreatmentCode(char* code);
void        initHotStones(Treatment* pTreatment, Room* pRoom, RoomType rType);
void        initMeniPedi(Treatment* pTreatment, Room* pRoom, RoomType rType);
void        describeTreatment(Treatment* pTreatment); // different implementation using union
void        freeTreatment(Treatment* pTreatment);
void        freeTreatmentWrapper(void* treatment);
void        printTreatmentTypes();
void        printTreatment(const Treatment* pTreatment);
void        printTreatmentHeaders();
const char* getTreatmentTypeString(int typeNum);
const int   getTreatmentDurationInt(int typeNum);
const int   getTreatmentPriceInt(int typeNum);

#endif
