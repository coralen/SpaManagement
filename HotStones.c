#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

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
		scanf("%d", &option);
	} while (option < 1 || option > HOT_STONES_TYPE_COUNT);
	pHotStones->type = (StonesType)(option - 1);
}

void getStonesPlacement(HotStones* pHotStones)
{
	int option;

	do {
		printf("Please choose one of the following placement types:\n");
		printHotStonesPlacement();
		scanf("%d", &option);
	} while (option < 1 || option > HOT_STONES_PLACEMENT_COUNT);
	pHotStones->type = (stonePlacement)(option - 1);
}

void printHotStonesType()
{
	for (int i = 0; i < HOT_STONES_TYPE_COUNT; i++)
		printf("%d - %s\n", i + 1, getStonesTypeString(i));
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

void printHotStones(const HotStones* pHotStones)
{
	printf("%-10s\t%-10s\t", getStonesTypeString(pHotStones->type), getStonesPlacementString(pHotStones->placement));
}

void printHotStonesHeaders()
{
	printf("Type%-10s\tPlacement%-10s\t", " ", " ");
}

int writeHotStonesToBFile(FILE* pFile, HotStones* pHotStones)
{
	if (fwrite(pHotStones, sizeof(HotStones), 1, pFile) != 1) return 0;
	return 1;
}

int readHotStonesFromBFile(FILE* pFile, HotStones* pHotStones)
{
	if (fread(pHotStones, sizeof(HotStones), 1, pFile) != 1) return 0;
	return 1;
}

int writeHotStonesToTextFile(FILE* pFile, HotStones* pHotStones)
{
	if (fprintf(pFile, "%d\n", pHotStones->type) < 0) return 0;
	if (fprintf(pFile, "%d\n", pHotStones->placement) < 0) return 0;
	return 1;
}

int readHotStonesFromTextFile(FILE* pFile, HotStones* pHotStones)
{
	if (!fscanf(pFile, "%d\n", &pHotStones->type)) return 0;
	if (!fscanf(pFile, "%d\n", &pHotStones->placement)) return 0;
	return 1;
}