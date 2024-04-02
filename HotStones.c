#include <stdio.h>

#include "HotStones.h"

static const char* stonesTypeString[HOT_STONES_TYPE_COUNT] = { "Basalt", "Marble" ,"Himalayan Salt" };
static const char* stonesPlacementString[HOT_STONES_PLACEMENT_COUNT] = { "Back", "Neck" ,"Hands", "Legs" };

void getHotStonesType(HotStones* pHotStones)
{
	int option;

	do {
		printf("Please choose one of the following stone types:\n");
		printHotStonesType();
		scanf_s("%d", &option);
	} while (option < 1 || option > HOT_STONES_TYPE_COUNT);
	pHotStones->sType = (StonesType)(option - 1);
}

void getStonesPlacement(HotStones* pHotStones)
{
	int option;

	do {
		printf("Please choose one of the following placement types:\n");
		printHotStonesPlacement();
		scanf_s("%d", &option);
	} while (option < 1 || option > HOT_STONES_PLACEMENT_COUNT);
	pHotStones->sType = (stonePlacement)(option - 1);
}

void printHotStonesType()
{
	for (int i = 0; i < HOT_STONES_TYPE_COUNT; i++)
		printf("%d - %s\n", i + 1, getStonesPlacementString(i));
}

void printHotStonesPlacement()
{
	for (int i = 0; i < HOT_STONES_PLACEMENT_COUNT; i++)
		printf("%d - %s\n", i + 1, getStonesPlacementString(i));
}

const char* getStonesTypeString(int typeNum)
{
	return stonesTypeString[typeNum];
}

const char* getStonesPlacementString(int typeNum)
{
	return stonesPlacementString[typeNum];
}
