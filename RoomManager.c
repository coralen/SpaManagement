#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "RoomManager.h"
#include "General.h"
#include "Date.h"

void initRoomManager(RoomManager* pRoomManager)
{
	pRoomManager->roomArr = NULL;
	pRoomManager->roomCount = 0;
}

int addRoom(RoomManager* pRoomManager)
{
	pRoomManager->roomArr = (Room*)realloc(pRoomManager->roomArr, (pRoomManager->roomCount + 1) * sizeof(Room));
	if (!pRoomManager->roomArr) return 0;

	initRoom(&pRoomManager->roomArr[pRoomManager->roomCount], pRoomManager);
	pRoomManager->roomCount++;
	return 1;

}

void initRoom(Room* pRoom, RoomManager* pRoomManager)
{
	while (1)
	{
		getRoomCode(pRoom->code);
		if (checkUniqueRoomCode(pRoom->code, pRoomManager))
			break;

		printf("This code already in use - enter a different code\n");
	}
	initRoomNoCode(pRoom);
}

int checkUniqueRoomCode(const char* code, RoomManager* pRoomManager)
{
	for (int i = 0; i < pRoomManager->roomCount; i++)
		if (!strcmp(code, pRoomManager->roomArr[i].code)) return 0;
	return 1;
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

Room* findRoomByCode(RoomManager* pRoomManager, char* code)
{
	for (int i = 0; i < pRoomManager->roomCount; i++)
	{
		if (!strcmp(pRoomManager->roomArr[i].code, code))
			return &pRoomManager->roomArr[i];
	}
	return NULL;
}

void printRoomArr(const RoomManager* pRoomManager)
{
	printRoomHeaders();
	printf("\n");
	for (int i = 0; i < pRoomManager->roomCount; i++)
		printRoom(&pRoomManager->roomArr[i]);
}


int writeRoomManagerToBFile(FILE* pFile, const RoomManager* pRoomManager)
{
	if (fwrite(&pRoomManager->roomCount, sizeof(int), 1, pFile) != 1) return 0;
	for (int i = 0; i < pRoomManager->roomCount; i++)
		if (!writeRoomToBFile(pFile, &pRoomManager->roomArr[i])) return 0;

	return 1;
}

int readRoomManagerFromBFile(FILE* pFile, RoomManager* pRoomManager)
{
	if (fread(&pRoomManager->roomCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!pRoomManager->roomCount) return 1;
	if (!(pRoomManager->roomArr = (Room*)realloc(pRoomManager->roomArr, (pRoomManager->roomCount) * sizeof(Room)))) return 0;
	
	// create a readRoomArr function
	for (int i = 0; i < pRoomManager->roomCount; i++)
	{
		Room* pRoom = (Room*)calloc(1, sizeof(Room));
		if (!readRoomFromBFile(pFile, pRoom)) return 0;
		pRoomManager->roomArr[i] = *pRoom;

	}
	return 1;
}

int writeRoomManagerToTextFile(FILE* pFile, const RoomManager* pRoomManager)
{
	if (fprintf(pFile, "%d\n", pRoomManager->roomCount) < 0) return 0;
	for (int i = 0; i < pRoomManager->roomCount; i++)
		if (!writeRoomToTextFile(pFile, &pRoomManager->roomArr[i])) return 0;

	return 1;
}

int readRoomManagerFromTextFile(FILE* pFile, RoomManager* pRoomManager)
{
	if (!fscanf(pFile, "%d\n", &pRoomManager->roomCount)) return 0;
	if (!pRoomManager->roomCount) return 1;
	if (!(pRoomManager->roomArr = (Room*)realloc(pRoomManager->roomArr, (pRoomManager->roomCount) * sizeof(Room)))) return 0;
	
	for (int i = 0; i < pRoomManager->roomCount; i++)
	{
		Room* pRoom = (Room*)calloc(1, sizeof(Room));
		if (!readRoomFromTextFile(pFile, pRoom)) return 0;
		pRoomManager->roomArr[i] = *pRoom;

	}
	return 1;
}
