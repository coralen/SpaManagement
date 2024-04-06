#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Massage.h"
#include "Helper.h"

static const char* massageTypeString[MASSAGE_TYPE_COUNT] = { "Swedish", "Deep Tissue" ,"Reflexology", "Shiatsu" };

void getMassageType(MassageType* type)
{
	int option;

	do {
		printf("Please choose one of the following massage types:\n");
		printMassageType();
		scanf("%d", &option);
	} while (option < 0 || option >= MASSAGE_TYPE_COUNT);
	*type = (MassageType)option;
}

int getNotesFromClient(char** notes)
{
	char inputMessage[MAX_STRING];

	while (getchar() != '\n');
	printf("Enter notes from the client:\n");
	scanf(SCANF_FORMAT, inputMessage);
	while (getchar() != '\n');

	if (!(*notes = (char*)malloc((strlen(inputMessage) + 1) * sizeof(char)))) return 0;
	strcpy(*notes, inputMessage);
	return 1;
}

void printMassageType()
{
	for (int i = 0; i < MASSAGE_TYPE_COUNT; i++)
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

void printMassageHeaders()
{
	printf("Type%-10s\tClient notes%-10s\t", " ", " ");
}

int writeMassageToBFile(FILE* pFile, Massage* pMassage)
{
	if (fwrite(&pMassage->type, sizeof(MassageType), 1, pFile) != 1) return 0;
	int len = strlen(pMassage->notesFromClient) + 1;
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

int writeMassageToTextFile(FILE* pFile, Massage* pMassage)
{
	if (fprintf(pFile, "%d\n", pMassage->type) < 0) return 0;
	if (fprintf(pFile, "%s\n", pMassage->notesFromClient) < 0) return 0;
	return 1;
}

int readMassageFromTextFile(FILE* pFile, Massage* pMassage)
{
	char tmpName[MAX_STRING] = { 0 };

	if (fscanf(pFile, "%d\n", &pMassage->type) < 0) return 0;
	if (!fscanf(pFile, " %[^\n]\n", tmpName)) return 0;
	pMassage->notesFromClient = strdup(tmpName);
	return 1;
}