#ifndef _ROOM_H
#define _ROOM_H

#include "Date.h"

#define ROOM_TYPE_COUNT 3

static const char* typeString[ROOM_TYPE_COUNT] = { "Massage", "Hot Stones" ,"Meni Pedi" };

typedef enum { MASSAGE, HOT_STONES, MENI_PEDI } RoomType;

typedef struct {
    RoomType type;
    Date date;
    int hour;
    int size;
    bool status;
} Room;

/*

Atrributes:
- status: boolean
- date: Date
- hour: int
- type: RoomType
- size: int

Functions:
None

Additional:
None

*/

#endif