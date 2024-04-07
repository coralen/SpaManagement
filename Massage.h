#ifndef _MASSAGE_H
#define _MASSAGE_H

#define MASSAGE_ROOM_TYPE 0
#define MASSAGE_EMPLOYEE_ROLE 1

typedef enum { eSwedish, eDeepTissue, eReflexologt, eShiatsu, eNoOfMassageType } MassageType;

typedef struct {
    MassageType type;
    char* notesFromClient;
} Massage;

int         getNotesFromClient(char** notes);
int         writeMassageToBFile(FILE* pFile, const Massage* pMassage);
int         readMassageFromBFile(FILE* pFile, Massage* pMassage);
int         writeMassageToTextFile(FILE* pFile, const Massage* pMassage);
int         readMassageFromTextFile(FILE* pFile, Massage* pMassage);
void        printMassageType();
void        printMassageHeaders(void* input);
void        getMassageType(MassageType* type);
void        printMassage(const Massage* pMassage);
void        freeMassage(Massage* pMassage);
const char* getMassageTypeString(int typeNum);

#endif