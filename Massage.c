#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Massage.h"
#include "Helper.h"

static const char* massageTypeString[eNoOfMassageType] = { "Swedish", "Deep Tissue" ,"Reflexology", "Shiatsu" };

void getMassageType(MassageType* type)
{
	int option;

	do {
		printf("Please choose one of the following massage types:\n");
		printMassageType();
		scanf("%d", &option);
	} while (option < 0 || option >= eNoOfMassageType);
	*type = (MassageType)option;
}

int getNotesFromClient(char** notes)
{
	char inputMessage[MAX_STRING];

	while (getchar() != '\n');
	printf("Enter notes from the client:\n");
	scanf(SCANF_FORMAT, inputMessage);
	while (getchar() != '\n');
	inputMessage[MAX_STRING - 1] = '\0';

	if (!(*notes = strdup(inputMessage))) return 0;
	return 1;
}

void printMassageType()
{
	for (int i = 0; i < eNoOfMassageType; i++)
		printf("%d - %s\n", i, getMassageTypeString(i));
}

const char* getMassageTypeString(int typeNum)
{
	return massageTypeString[typeNum];
}

void printMassage(const Massage* pMassage)
{
	printf("%-10s\t%-10s\t", getMassageTypeString(pMassage->type), pMassage->notesFromClient);
}

void printMassageHeaders(void* input)
{
	printf("Type%-10s\tClient notes%-10s\t", " ", " ");
}

int writeMassageToBFile(FILE* pFile, const Massage* pMassage)
{
	if (fwrite(&pMassage->type, sizeof(MassageType), 1, pFile) != 1) return 0;
	int len = (int)(strlen(pMassage->notesFromClient) + 1);
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pMassage->notesFromClient, sizeof(char), len, pFile) != len) return 0;

	return 1;
}

int readMassageFromBFile(FILE* pFile, Massage* pMassage)
{
	int len;

	if (fread(&pMassage->type, sizeof(MassageType), 1, pFile) != 1) return 0;
	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (!(pMassage->notesFromClient = (char*)malloc(len * sizeof(char)))) return 0;
	if (fread(pMassage->notesFromClient, sizeof(char), len, pFile) != len) return 0;
	return 1;
}

int writeMassageToTextFile(FILE* pFile, const Massage* pMassage)
{
	if (fprintf(pFile, "%d\n", pMassage->type) < 0) return 0;
	if (fprintf(pFile, "%s\n", pMassage->notesFromClient) < 0) return 0;
	return 1;
}

int readMassageFromTextFile(FILE* pFile, Massage* pMassage)
{
	char tmpName[MAX_STRING] = { 0 };

	if (fscanf(pFile, "%d\n", (int*)&pMassage->type) < 0) return 0;
	if (!fscanf(pFile, " %[^\n]\n", tmpName)) return 0;
	pMassage->notesFromClient = strdup(tmpName);
	return 1;
}

void freeMassage(Massage* pMassage)
{
	CHECK_NULL(pMassage);
	free(pMassage->notesFromClient);
}