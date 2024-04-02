#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"
#include "Def.h"

#define ROOM_START_CHAR "R-"
#define ROOM_TYPE_COUNT 2

static const char* roomTypeString[ROOM_TYPE_COUNT] = { "Bedded", "Chaired" };

typedef enum { BEDDED, CHAIRED } RoomType;

typedef struct {
    char code[CODE];
    RoomType type;
    Date date;
    int size;
    BOOL isBooked;
} Room;

void initRoomNoCode(Room* pRoom);
void getSize(Room* pRoom);
void getRoomType(Room* pRoom);
void getRoomCode(char* code);
void printRoomTypes();

#endif