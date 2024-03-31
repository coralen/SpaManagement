#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Room.h"
#include "General.h"

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
    int choice;

    printf("Choose one of the room types:\n");
    printRoomTypes();
    scanf("%d", &choice);
    pRoom->type = (RoomType)choice;
}

void getRoomCode(char* code)
{
    char inputCode[MAX_STRING];
    do {
        printf("Enter treatment code, Format is R- following %d UPPER CASE letters\n", CODE);
        scanf(" %[^\n]", &inputCode);
    } while (!isCodeValid(inputCode, ROOM_START_CHAR));

    printf("\n");
    strcpy(code, inputCode);
}

void printRoomTypes()
{
    for (int i = 0; i < ROOM_TYPE_COUNT; i++)
        printf("%d - %s\n", i, typeString[i]);
}