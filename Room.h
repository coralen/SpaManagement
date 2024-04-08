#ifndef _ROOM_H
#define _ROOM_H

#include <stdio.h>

#include "Date.h"
#include "Def.h"
#include "General.h"

#define ROOM_START_CHAR "R-"

typedef enum { eBedded, eChaired, eNoOfRoomType } RoomType;

typedef struct {
    char code[TOTAL_CODE + 1];
    RoomType type;
    int size;
    BOOL isBooked;
} Room;

int         writeRoomToBFile(FILE* pFile, const Room* pRoom);
int         readRoomFromBFile(FILE* pFile, Room* pRoom);
int         writeRoomToTextFile(FILE* pFile, const Room* pRoom);
int         readRoomFromTextFile(FILE* pFile, Room* pRoom);
void        initRoomNoCode(Room* pRoom);
void        setRoomSize(Room* pRoom);
void        setRoomType(Room* pRoom);
void        setRoomCode(char* code);
void        printRoomTypes();
void        printRoom(const Room* pRoom);
void        printRoomWrapper(void* pRoom);
void        printRoomHeaders();
const char* getRoomTypeString(int typeNum);

#endif