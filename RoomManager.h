#ifndef _ROOM_MANAGER_H
#define _ROOM_MANAGER_H

#include "Room.h"
typedef struct {
    Room* roomArr;
    int roomCount;
} RoomManager;

int initRoomManager(RoomManager* pRoomManager);
int addRoom(RoomManager* pRoomManager);
void initRoom(Room* pRoom, RoomManager* pRoomManager);
void deleteRoom(Room* pRoom);
Room* getAvailableRoom(RoomManager* pRoomManager, RoomType type);
//void findRoomByType(); // no need?


#endif