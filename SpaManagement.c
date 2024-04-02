#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "RoomManager.h"
#include "TreatmentManager.h"

int addTreatment(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager)
{
	if (!checkRequirments(pTreatmentManager, pRoomManager)) return 0;

	int option;
	RoomType rType;
	Room* pRoom;

	printf("\n");
	
	do {
		printf("Please choose the type of treatment:\n");
		for (int i = 0; i < TREATMENT_TYPE_COUNT; i++)
			printf("Enter %d for %s\n", i + 1, treatmentTypeString[i]);
		scanf("%d", &option);
	} while (option < 1 || option > TREATMENT_TYPE_COUNT);

	switch (option - 1)
	{
	case 1:
		rType = (RoomType)MASSAGE_ROOM_TYPE;
		break;

	case 2:
		rType = (RoomType)HOT_STONES_ROOM_TYPE;
		break;

	case 3:
		rType = (RoomType)MENI_PEDI_ROOM_TYPE;
	}

	pRoom = findAvailableRoom(pRoomManager, rType);
	if (!pRoom)
	{
		printf("No available room for this treatment!\n");
		return 0;
	}

	/* Talya - add findAvailableEmployee */
	Treatment* pTreatment = (Treatment*)calloc(1, sizeof(Treatment));
	if (!pTreatment) return 0;

	initTreatment(pTreatment, pTreatmentManager, option, pRoom, rType);
	addTreatmentToList(pTreatment, pTreatmentManager);
	return 1;

}

int checkRequirments(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager)
{
	/* Talya -  check if there are enought employees */
	if (!pRoomManager->roomCount)
	{
		printf("Not enough rooms to add a new treatment!\n");
		return 0;
	}
	return 1;
}
