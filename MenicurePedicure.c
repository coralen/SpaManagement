#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/Helper.h"
#include "../headers/General.h"
#include "../headers/MenicurePedicure.h"

static const char* NailTypeString[eNoNailArtType] = { "ChromePowder", "Sticker", "French" };

void setMedicoreAndPedicore(MenicurePedicure* MediPedi) 
{
    int choice, validFlag = 0;
    
    do {
        printf("Do you want to get medicure?\n");
        printBoolType();
        scanf("%d", &choice);
        if (choice > -1 && choice < eNofBool)
        {
            MediPedi->menicure = (BOOL)choice;
            validFlag = 1;
        }
        else printf("Invalid choice, try again\n");
    } while (!validFlag);
    
    validFlag = 0;

    do {
        printf("Do you want to get pedicure?\n");
        printBoolType();
        scanf("%d", &choice);
        if (choice > -1 && choice < 2)
        {
            MediPedi->pedicure = (BOOL)choice;
            validFlag = 1;
        }
        else printf("Invalid choice, try again\n");
    } while (!validFlag);
}

int setPolishColor(char** color) 
{
    char colorInput[MAX_STRING];

    printf("Enter the nail polish color you want:\n");
    while (getchar() != '\n');
    scanf(SCANF_FORMAT, colorInput);
    while (getchar() != '\n');
    if (!(*color = (char*)malloc((strlen(colorInput) + 1) * sizeof(char)))) return 0;
    strcpy(*color, colorInput);
    capitalFirst(*color);

    return 1;
}


void setNailArtType(MenicurePedicure* MediPedi) 
{
    int numType, validFlag = 0;

    do
    {
        printf("Enter the type of your nail art, the options are:\n");
        printNailArtType();
        scanf("%d", &numType);
        if (numType >= 0 && numType < eNoNailArtType)
        {
            MediPedi->nailArtType = numType;
            validFlag = 1;
        }
        else printf("Invalid choice, try again\n");
    } while (!validFlag);
}

void printNailArtType()
{
    for (int i = 0; i < eNoNailArtType; i++)
        printf("%d - %s\n", i, getNailArtTypeString(i));
}

const char* getNailArtTypeString(const int typeNum)
{
    return NailTypeString[typeNum];
}

void printMenicurePedicure(const MenicurePedicure* pMeniPedi)
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t", pMeniPedi->color, getBoolString(pMeniPedi->menicure), getBoolString(pMeniPedi->pedicure), getNailArtTypeString(pMeniPedi->nailArtType));
}

void printMenicurePedicureHeaders(void* input)
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t", "Color", "Menicure", "Pedicure", "Nail art");
}

int writeMenicurePedicureToBFile(FILE* pFile, const MenicurePedicure* pMeniPedi)
{
    int len = (int)(strlen(pMeniPedi->color) + 1);
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pMeniPedi->color, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pMeniPedi->menicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fwrite(&pMeniPedi->pedicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fwrite(&pMeniPedi->nailArtType, sizeof(eNailArtType), 1, pFile) != 1) return 0;
    return 1;
}

int readMenicurePedicureFromBFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    int len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (!(pMeniPedi->color = (char*)malloc(len * sizeof(char)))) return 0;
    if (fread(pMeniPedi->color, sizeof(char), len, pFile) != len) return 0;
    if (fread(&pMeniPedi->menicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fread(&pMeniPedi->pedicure, sizeof(BOOL), 1, pFile) != 1) return 0;
    if (fread(&pMeniPedi->nailArtType, sizeof(eNailArtType), 1, pFile) != 1) return 0;

    return 1;
}

int writeMenicurePedicureToTextFile(FILE* pFile, const MenicurePedicure* pMeniPedi)
{
    if (fprintf(pFile, "%s\n", pMeniPedi->color) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->menicure) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->pedicure) < 0) return 0;
    if (fprintf(pFile, "%d\n", pMeniPedi->nailArtType) < 0) return 0;
    return 1;
}

int readMenicurePedicureFromTextFile(FILE* pFile, MenicurePedicure* pMeniPedi)
{
    char tmpColor[MAX_STRING] = { 0 };

    if (!fscanf(pFile, " %[^\n]\n", tmpColor)) return 0;
    pMeniPedi->color = strdup(tmpColor);

    if (!fscanf(pFile, "%d\n", &pMeniPedi->menicure)) return 0;
    if (!fscanf(pFile, "%d\n", &pMeniPedi->pedicure)) return 0;
    if (!fscanf(pFile, "%d\n", &pMeniPedi->nailArtType)) return 0;
    return 1;
}

void freeMenicurePedicure(MenicurePedicure* pMeniPedi)
{
    CHECK_NULL(pMeniPedi);
    free(pMeniPedi->color);
}