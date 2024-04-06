#ifndef _ROOM_MANAGER_H
#define _ROOM_MANAGER_H

#include "Room.h"

typedef struct {
    Room* roomArr;
    int roomCount;
} RoomManager;


int     addRoom(RoomManager* pRoomManager);
int     findRoomIndexInArray(const Room* pRoom, const RoomManager* pRoomManager);
int     checkUniqueRoomCode(const char* code, RoomManager* pRoomManager);
int     deleteRoom(Room* pRoom, RoomManager* pRoomManager);
int     writeRoomManagerToBFile(FILE* pFile, const RoomManager* pRoomManager);
int     readRoomManagerFromBFile(FILE* pFile, RoomManager* pRoomManager);
int     writeRoomManagerToTextFile(FILE* pFile, const RoomManager* pRoomManager);
int     readRoomManagerFromTextFile(FILE* pFile, RoomManager* pRoomManager);
void    initRoomManager(RoomManager* pRoomManager);
void    initRoom(Room* pRoom, RoomManager* pRoomManager);
void    printRoomArr(const RoomManager* pRoomManager);
Room*   findRoomByCode(RoomManager* pRoomManager, char* code);


#endif