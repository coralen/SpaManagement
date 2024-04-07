#ifndef _MASSAGE_H
#define _MASSAGE_H

#define MASSAGE_TYPE_COUNT 4
#define MASSAGE_ROOM_TYPE 0
#define MASSAGE_EMPLOYEE_ROLE 1


typedef enum { SWEDISH, DEEP_TISSUE, REFLEXOLOGY, SHIATSU } MassageType;

typedef struct {
    MassageType type;
    char* notesFromClient;
} Massage;

int         getNotesFromClient(char** notes);
int         writeMassageToBFile(FILE* pFile, Massage* pMassage);
int         readMassageFromBFile(FILE* pFile, Massage* pMassage);
int         writeMassageToTextFile(FILE* pFile, Massage* pMassage);
int         readMassageFromTextFile(FILE* pFile, Massage* pMassage);
void        printMassageType();
void        printMassageHeaders();
void        getMassageType(MassageType* type);
void        printMassage(const Massage* pMassage);
void        freeMassage(Massage* pMassage);
const char* getMassageTypeString(int typeNum);

#endif