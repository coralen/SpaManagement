#ifndef _MEDICUREPEDICORE_H
#define _MEDICUREPEDICORE_H

#pragma once

#include "General.h"
#include "helper.h"

typedef enum {
    eChromePowder, eSticker, eFrench, eNoType
} eNailArtType;

static const char* NailType[eNoType]
        = { "ChromePowder", "Sticker", "French"};

typedef struct
{
    char* color;
    BOOL Manicure;
    BOOL Pedicore;
    eNailArtType NailArtType;
}MedicurePedicore;

void setMedicoreAndPedicore(MedicurePedicore* MediPedi);
void setPolishColor(MedicurePedicore* MediPedi, char* color);
void setNailArtType(MedicurePedicore* MediPedi);

#endif