#include <stdio.h>

#include "Massage.h"

/* implement 
*  getMassageType(&pTreatment->data.massage.mType);
*  getNotesFromClient(&pTreatment->data.massage.notesFromClient);
*/

void getMassageType(Massage* pMassage)
{	
	int option;

	do {
		printf("Please choose one of the following massage types:\n");
		printMassageType();
		scanf("%d", &option);
	} while (option < 1 || option > MASSAGE_TYPE_COUNT);
	pMassage->mType = (MassageType)(option - 1);
}

int getNotesFromClient(Massage* pMassage)
{
	char inputMessage[MAX_STRING];
	printf("Enter notes from the client:\n", CODE);
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
