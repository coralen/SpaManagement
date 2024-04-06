#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "General.h"
#include "MenicurePedicure.h"

static const char* NailTypeString[eNoNailArtType] = { "ChromePowder", "Sticker", "French" };

void setMedicoreAndPedicore(MenicurePedicure* MediPedi) 
{
    printf("Do you want to get medicure? \n0 - no\n1 - yes\n ");
    int choise;
    scanf("%d", &choise);
    if (choise == 1) MediPedi->Manicure = True;

    printf("Do you want to get pedicore? \n0 - no\n1 - yes\n ");
    scanf("%d", &choise);
    if (choise == 1) MediPedi->Pedicure = True;
}

int setPolishColor(char** color) 
{
    char colorInput[MAX_STRING];

    printf("Enter the nail polish color you want: \n");
    while (getchar() != '\n');
    scanf(SCANF_FORMAT, colorInput);
    while (getchar() != '\n');
    if (!(*color = (char*)malloc((strlen(colorInput) + 1) * sizeof(char)))) return 0;
    strcpy(*color, colorInput);
    return 1;
}


void setNailArtType(MenicurePedicure* MediPedi) 
{
    printf("Enter the type of your nail art, the options are:\n");
    printNailArtType();
    int numType;
    scanf("%d", &numType);
    if (numType >= 0 && numType < eNoNailArtType)
        MediPedi->NailArtType = numType;
    else printf("Invalid type number\n");
}

void printNailArtType()
{
    for (int i = 0; i < eNoNailArtType; i++)
        printf("%d - %s\n", i, getNailArtTypeString(i));
}

const char* getNailArtTypeString(int typeNum)
{
    return NailTypeString[typeNum];
}

void printMenicurePedicure(const MenicurePedicure* pMeniPedi)
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t", pMeniPedi->color, getBoolString(pMeniPedi->Manicure), getBoolString(pMeniPedi->Manicure), getNailArtTypeString(pMeniPedi->NailArtType));
}

void printMenicurePedicureHeaders()
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t", "Color", "Menicure", "Pedicure", "Nail art");
}

int writeMenicurePedicureToBFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    int len = strlen(pMeniPedi->color) + 1;
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pMeniPedi->color, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pMeniPedi->Manicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fwrite(&pMeniPedi->Pedicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fwrite(&pMeniPedi->NailArtType, sizeof(eNailArtType), 1, pFile) != 1) return 0;
    return 1;
}

int readMenicurePedicureFromBFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    int len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (!(pMeniPedi->color = (char*)malloc(len * sizeof(char)))) return 0;
    if (fread(pMeniPedi->color, sizeof(char), len, pFile) != len) return 0;
    if (fread(&pMeniPedi->Manicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fread(&pMeniPedi->Pedicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fread(&pMeniPedi->NailArtType, sizeof(eNailArtType), 1, pFile) != 1) return 0;

    return 1;
}

int writeMenicurePedicureToTextFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    if (fprintf(pFile, "%s\n", pMeniPedi->color) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->Manicure) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->Pedicure) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->NailArtType) < 0) return 0;
    return 1;
}

int readMenicurePedicureFromTextFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    char tmpColor[MAX_STRING] = { 0 };

    if (!fscanf(pFile, " %[^\n]\n", tmpColor)) return 0;
    pMeniPedi->color = strdup(tmpColor);

    if (!fscanf(pFile, "%d\n", &pMeniPedi->Manicure)) return 0;
    if (!fscanf(pFile, "%d\n", &pMeniPedi->Pedicure)) return 0;
    if (!fscanf(pFile, "%d\n", &pMeniPedi->NailArtType)) return 0;
    return 1;
}