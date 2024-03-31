#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"
#include "Def.h"

#define ROOM_TYPE_COUNT 3
#define ROOM_START_CHAR "R-"

static const char* typeString[ROOM_TYPE_COUNT] = { "Massage", "Hot Stones" ,"Meni Pedi" };

typedef enum { MASSAGE, HOT_STONES, MENI_PEDI } RoomType;

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