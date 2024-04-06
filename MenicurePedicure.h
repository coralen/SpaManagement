#ifndef _MEDICUREPEDICURE_H
#define _MEDICUREPEDICURE_H

#pragma once

#include "General.h"
#include "helper.h"

#define MENI_PEDI_ROOM_TYPE 1
#define MENI_PEDI_EMPLOYEE_ROLE 2

typedef enum {
    eChromePowder, eSticker, eFrench, eNoType
} eNailArtType;

static const char* NailType[eNoType] = { "ChromePowder", "Sticker", "French" };

typedef struct
{
    char* color;
    BOOL Manicure;
    BOOL Pedicure;
    eNailArtType NailArtType;
} MenicurePedicure;

int     setPolishColor(char** color);
int     writeMenicurePedicureToBFile(FILE* pFile, MenicurePedicure* pMeniPedi);
int     readMenicurePedicureFromBFile(FILE* pFile, MenicurePedicure* pMeniPedi);
int     writeMenicurePedicureToTextFile(FILE* pFile, MenicurePedicure* pMeniPedi);
int     readMenicurePedicureFromTextFile(FILE* pFile, MenicurePedicure* pMeniPedi);
void    setMedicoreAndPedicore(MenicurePedicure* MediPedi);
void    setNailArtType(MenicurePedicure* MediPedi);
void    printMenicurePedicure(const MenicurePedicure* pMeniPedi);
void    printMenicurePedicureHeaders();

#endif