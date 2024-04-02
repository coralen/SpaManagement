#ifndef _ROOM_MANAGER_H
#define _ROOM_MANAGER_H

#include "Room.h"
typedef struct {
    Room* roomArr;
    int roomCount;
} RoomManager;

int initRoomManager(RoomManager* pRoomManager);
int addRoom(RoomManager* pRoomManager);
int findRoomIndexInArray(const Room* pRoom, const RoomManager* pRoomManager);
void initRoom(Room* pRoom, RoomManager* pRoomManager);
int checkUniqueRoomCode(const char* code, RoomManager* pRoomManager);
int deleteRoom(Room* pRoom, RoomManager* pRoomManager);
Room* findAvailableRoom(RoomManager* pRoomManager, RoomType type);


#endif