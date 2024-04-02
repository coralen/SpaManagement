#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "Massage.h"
#include "Helper.h"

void getMassageType(Massage* pMassage)
{	
	int option;

	do {
		printf("Please choose one of the following massage types:\n");
		printMassageType();
		scanf_s("%d", &option);
	} while (option < 1 || option > MASSAGE_TYPE_COUNT);
	pMassage->mType = (MassageType)(option - 1);
}

int getNotesFromClient(Massage* pMassage)
{
	char inputMessage[MAX_STRING];
	printf("Enter notes from the client:\n");
	scanf(" %[^\n]", &inputMessage);
	printf("\n");
	pMassage->notesFromClient = strdup(inputMessage);
	if (!pMassage->notesFromClient) return 0;
	return 1;
}

void printMassageType()
{
	for (int i = 0; i < MASSAGE_TYPE_COUNT; i++)
		printf("%d - %s\n", i + 1, massageTypeString[i]);
}
