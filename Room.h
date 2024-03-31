#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"
#include "Def.h"

#define ROOM_TYPE_COUNT 3

static const char* typeString[ROOM_TYPE_COUNT] = { "Massage", "Hot Stones" ,"Meni Pedi" };

typedef enum { MASSAGE, HOT_STONES, MENI_PEDI } RoomType;

typedef struct {
    char code[CODE];
    RoomType type;
    Date date;
    int size;
    BOOL status;
} Room;

void initRoomNoCode(Room* pRoom);

#endif