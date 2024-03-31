#define _CRT_SECURE_NO_WARNINGS

#include "Room.h"

void initRoomNoCode(Room* pRoom)
{
	getCorrectDate(&pRoom->date);
	getSize(pRoom);
	pRoom->status = (BOOL)0;
	getRoomType(pRoom);
}