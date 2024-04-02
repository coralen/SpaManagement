#ifndef _MASSAGE_H
#define _MASSAGE_H

#include "Treatment.h"

#define MASSAGE_TYPE_COUNT 4
#define MASSAGE_ROOM_TYPE 0

static const char* massageTypeString[MASSAGE_TYPE_COUNT] = { "Swedish", "Deep Tissue" ,"Reflexology", "Shiatsu" };

typedef enum { SWEDISH, DEEP_TISSUE, REFLEXOLOGY, SHIATSU } MassageType;

typedef struct {
    MassageType mType;
    char* notesFromClient;
} Massage;

void printMassageType();
void getMassageType(Massage* pMassage);
int getNotesFromClient(Massage* pMassage);


#endif