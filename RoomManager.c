#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstddef>
#include <stdlib.h>

#include "RoomManager.h"
#include "General.h"
#include "Date.h"

int initRoomManager(RoomManager* pRoomManager)
{
	pRoomManager->roomArr = NULL;
	pRoomManager->roomCount = 0;
	return 1;
}

int addRoom(RoomManager* pRoomManager)
{
	Room* pRoom = (Room*)calloc(1, sizeof(Room));
	if (!pRoom) return 0;

	initRoom(pRoom, pRoomManager);

	pRoomManager->roomArr = (Room*)realloc(pRoomManager->roomArr, (pRoomManager->roomCount + 1) * sizeof(Room));
	if (!pRoomManager->roomArr)
	{
		free(pRoom);
		return 0;
	}

	pRoomManager->roomArr[pRoomManager->roomCount] = *pRoom;
	pRoomManager->roomCount++;
	return 1;

}

void initRoom(Room* pRoom, RoomManager* pRoomManager)
{
	while (1)
	{
		getRoomCode(pRoom->code);
		if (checkUniqeCode(pRoom->code, pRoomManager))
			break;

		printf("This code already in use - enter a different code\n");
	}
	initRoomNoCode(pRoom);
}

int deleteRoom(Room* pRoom, RoomManager* pRoomManager)
{
	int location = findRoomIndexInArray(pRoom, pRoomManager);
	if (location == -1) return 0;

	for (int i = location; i < pRoomManager->roomCount; i++)
		pRoomManager->roomArr[i] = pRoomManager->roomArr[i + 1];
	pRoomManager->roomCount--;

	Room* tempRoomArray = realloc(pRoomManager->roomArr, pRoomManager->roomCount * sizeof(Room));
	if (tempRoomArray != NULL || pRoomManager->roomCount == 0)
		pRoomManager->roomArr = tempRoomArray;
	else return 0;

	return 1;
}

int findRoomIndexInArray(const Room* pRoom, const RoomManager* pRoomManager)
{
	for (int i = 0; i < pRoomManager->roomCount; i++) 
		if (&pRoomManager->roomArr[i] == pRoom)
			return i;
	return -1;
}

Room* getAvailableRoom(RoomManager* pRoomManager, RoomType type)
{
	for (int i = 0; i < pRoomManager->roomCount; i++)
	{
		if (pRoomManager->roomArr[i].type == type && !pRoomManager->roomArr[i].isBooked)
			return &pRoomManager->roomArr[i];
	}
	return NULL;
}


