#ifndef _MASSAGE_H
#define _MASSAGE_H

#define MASSAGE_TYPE_COUNT 4
#define MASSAGE_ROOM_TYPE 0

typedef enum { SWEDISH, DEEP_TISSUE, REFLEXOLOGY, SHIATSU } MassageType;

typedef struct {
    MassageType mType;
    char* notesFromClient;
} Massage;

int         getNotesFromClient(Massage* pMassage);
void        printMassageType();
void        getMassageType(Massage* pMassage);
const char* getMassageTypeString(int typeNum);

#endif