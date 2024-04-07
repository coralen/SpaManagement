#ifndef _MEDICUREPEDICURE_H
#define _MEDICUREPEDICURE_H

#pragma once

#include "General.h"
#include "helper.h"

#define MENI_PEDI_ROOM_TYPE 1
#define MENI_PEDI_EMPLOYEE_ROLE 2

typedef enum {
    eChromePowder, eSticker, eFrench, eNoNailArtType
} eNailArtType;

typedef struct
{
    char* color;
    BOOL menicure;
    BOOL pedicure;
    eNailArtType nailArtType;
} MenicurePedicure;

int         setPolishColor(char** color);
int         writeMenicurePedicureToBFile(FILE* pFile, const MenicurePedicure* pMeniPedi);
int         readMenicurePedicureFromBFile(FILE* pFile, MenicurePedicure* pMeniPedi);
int         writeMenicurePedicureToTextFile(FILE* pFile, const MenicurePedicure* pMeniPedi);
int         readMenicurePedicureFromTextFile(FILE* pFile, MenicurePedicure* pMeniPedi);
void        printNailArtType();
void        setMedicoreAndPedicore(MenicurePedicure* MediPedi);
void        setNailArtType(MenicurePedicure* MediPedi);
void        printMenicurePedicure(const MenicurePedicure* pMeniPedi);
void        printMenicurePedicureHeaders(void* input);
void        freeMenicurePedicure(MenicurePedicure* pMeniPedi);
const char* getNailArtTypeString(int typeNum);

#endif