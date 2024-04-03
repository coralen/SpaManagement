#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Room.h"
#include "General.h"

static const char* roomTypeString[ROOM_TYPE_COUNT] = { "Bedded", "Chaired" };

void initRoomNoCode(Room* pRoom)
{
	getCorrectDate(&pRoom->date);
	getSize(pRoom);
	pRoom->isBooked = (BOOL)0;
	getRoomType(pRoom);
}

void getSize(Room* pRoom)
{
    printf("Enter the room size:\n");
    scanf("%d", &pRoom->size);
}

void getRoomType(Room* pRoom)
{
    int choice = -1;

    do {
        printf("Choose one of the room types:\n");
        printRoomTypes();
        scanf("%d", &choice);
    } while (choice < 0 || choice > ROOM_TYPE_COUNT - 1);

    pRoom->type = (RoomType)choice;
    printf("%s\n", pRoom->code);
}

void getRoomCode(char* code)
{
    char inputCode[MAX_STRING];
    do {
        printf("Enter Room code, Format is %s following %d UPPER CASE letters\n", ROOM_START_CHAR, CODE);
        scanf(" %[^\n]", inputCode);
    } while (!isCodeValid(inputCode, ROOM_START_CHAR));

    printf("\n");
    strcpy(code, inputCode);
}

void printRoomTypes()
{
    for (int i = 0; i < ROOM_TYPE_COUNT; i++)
        printf("%d - %s\n", i, getRoomTypeString(i));
}

const char* getRoomTypeString(int typeNum)
{
    return roomTypeString[typeNum];
}

void printRoom(const Room* pRoom)
{
    printf("code: %s, size: %d, type: %s\n", pRoom->code, pRoom->size, getRoomTypeString(pRoom->type));
}