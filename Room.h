#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"
#include "Def.h"

#define ROOM_START_CHAR "R-"
#define ROOM_TYPE_COUNT 2

typedef enum { BEDDED, CHAIRED } RoomType;

typedef struct {
    char code[TOTAL_CODE + 1];
    RoomType type;
    Date date;
    int size;
    BOOL isBooked;
} Room;

void        initRoomNoCode(Room* pRoom);
void        getSize(Room* pRoom);
void        getRoomType(Room* pRoom);
void        getRoomCode(char* code);
void        printRoomTypes();
void        printRoom(const Room* pRoom);
void        printRoomHeaders();
const char* getRoomTypeString(int typeNum);

#endif