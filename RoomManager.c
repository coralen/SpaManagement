#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstddef>

#include "RoomManager.h"
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

void getRoomCode(pRoom, pRoomManager)
{

}

void deleteRoom(Room* pRoom)
{}

Room* getAvailableRoom(RoomManager* pRoomManager, RoomType type)
{}


