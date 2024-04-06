#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"
#include "Def.h"
#include "General.h"

#define ROOM_START_CHAR "R-"
#define ROOM_TYPE_COUNT 2

typedef enum { BEDDED, CHAIRED } RoomType;

typedef struct {
    char code[TOTAL_CODE + 1];
    RoomType type;
    int size;
    BOOL isBooked;
} Room;

int         writeRoomToBFile(FILE* pFile, Room* pRoom);
int         readRoomFromBFile(FILE* pFile, Room* pRoom);
int         writeRoomToTextFile(FILE* pFile, Room* pRoom);
int         readRoomFromTextFile(FILE* pFile, Room* pRoom);
void        initRoomNoCode(Room* pRoom);
void        getSize(Room* pRoom);
void        getRoomType(Room* pRoom);
void        getRoomCode(char* code);
void        printRoomTypes();
void        printRoom(const Room* pRoom);
void        printRoomHeaders();
const char* getRoomTypeString(int typeNum);

#endif