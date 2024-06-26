#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Room.h"
#include "General.h"

static const char* roomTypeString[eNoOfRoomType] = { "Bedded", "Chaired" };

void initRoomNoCode(Room* pRoom)
{
    setRoomType(pRoom);
    setRoomSize(pRoom);
    pRoom->isBooked = (BOOL)0;
}

void setRoomSize(Room* pRoom)
{
    printf("Enter the room size:\n");
    scanf("%d", &pRoom->size);
}

void setRoomType(Room* pRoom)
{
    int choice = -1;

    do {
        printf("Choose one of the room types:\n");
        printRoomTypes();
        scanf("%d", &choice);
    } while (choice < 0 || choice >= eNoOfRoomType);

    pRoom->type = (RoomType)choice;
}

void setRoomCode(char* code)
{
    char inputCode[MAX_STRING];
    do {
        printf("Enter Room code, Format is %s%s following %d digits\n", ROOM_START_CHAR, CODE_EXPECTED, CODE);
        scanf(SCANF_FORMAT, inputCode); 
        while (getchar() != '\n'); 
    } while (!isCodeValid(inputCode, ROOM_START_CHAR));

    strcpy(code, inputCode);
}

void printRoomTypes()
{
    for (int i = 0; i < eNoOfRoomType; i++)
        printf("%d - %s\n", i, getRoomTypeString(i));
}

const char* getRoomTypeString(int typeNum)
{
    return roomTypeString[typeNum];
}

void printRoom(const Room* pRoom)
{
    printf("%-10s\t%-10d\t%-10s\t%-10s\n", pRoom->code, pRoom->size, getRoomTypeString(pRoom->type), getStatusString(pRoom->isBooked));
}

void printRoomWrapper(void* pRoom)
{
    const Room* room = (const Room*)pRoom;
    printRoom(room);
}

void printRoomHeaders()
{
    printf("%-10s\t%-10s\t%-10s\t%-10s\t", "Code", "Size", "Type", "isBooked");

}

int writeRoomToBFile(FILE* pFile, const Room* pRoom)
{
    int len = (int)(strlen(pRoom->code));
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pRoom->code, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pRoom->type, sizeof(RoomType), 1, pFile) != 1) return 0;
    if (fwrite(&pRoom->size, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pRoom->isBooked, sizeof(BOOL), 1, pFile) != 1) return 0;

    return 1;
}

int readRoomFromBFile(FILE* pFile, Room* pRoom)
{
    int len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (len >= MAX_STRING ) return 0;
    if (fread(pRoom->code, sizeof(char), len, pFile) != len) return 0;
    pRoom->code[TOTAL_CODE] = '\0';

    if (fread(&pRoom->type, sizeof(RoomType), 1, pFile) != 1) return 0;
    if (fread(&pRoom->size, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pRoom->isBooked, sizeof(BOOL), 1, pFile) != 1) return 0;

    return 1;
}


int writeRoomToTextFile(FILE* pFile, const Room* pRoom)
{
    if (fprintf(pFile, "%s\n", pRoom->code) < 0) return 0;
    if (fprintf(pFile, "%d\n", pRoom->type) < 0) return 0;
    if (fprintf(pFile, "%d\n", pRoom->size) < 0) return 0;
    if (fprintf(pFile, "%d\n", pRoom->isBooked) < 0) return 0;

    return 1;
}

int readRoomFromTextFile(FILE* pFile, Room* pRoom)
{
    if (!fscanf(pFile, " %s\n", pRoom->code)) return 0;
    if (!fscanf(pFile, " %d\n", (int*)&pRoom->type)) return 0;
    if (!fscanf(pFile, " %d\n", &pRoom->size)) return 0;
    if (!fscanf(pFile, " %d\n", (int*)&pRoom->isBooked)) return 0;

    return 1;
}