#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "HotStones.h"

static const char* stonesTypeString[eNofStoneType] = { "Basalt", "Marble" ,"Himalayan Salt" };
static const char* stonesPlacementString[eNofPlacements] = { "Back", "Neck" ,"Hands", "Legs" };

void getHotStonesType(HotStones* pHotStones)
{
	int option;

	do {
		printf("Please choose one of the following stone types:\n");
		printHotStonesType();
		scanf("%d", &option);
	} while (option < 1 || option > eNofStoneType);
	pHotStones->type = (StonesType)(option - 1);
}

void getStonesPlacement(HotStones* pHotStones)
{
	int option;

	do {
		printf("Please choose one of the following placement types:\n");
		printHotStonesPlacement();
		scanf("%d", &option);
	} while (option < 1 || option > eNofPlacements);
	pHotStones->type = (stonePlacement)(option - 1);
}

void printHotStonesType()
{
	for (int i = 0; i < eNofStoneType; i++)
		printf("%d - %s\n", i + 1, getStonesTypeString(i));
}

void printHotStonesPlacement()
{
	for (int i = 0; i < eNofPlacements; i++)
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

int writeHotStonesToBFileOLD(FILE* pFile, HotStones* pHotStones)
{
	if (fwrite(pHotStones, sizeof(HotStones), 1, pFile) != 1) return 0;
	return 1;
}

int readHotStonesFromBFileOLD(FILE* pFile, HotStones* pHotStones)
{
	if (fread(pHotStones, sizeof(HotStones), 1, pFile) != 1) return 0;
	return 1;
}

int writeHotStonesToBFile(FILE* pCFile, HotStones* pHotStones)
{
	unsigned char data = 0;

	data |= pHotStones->type << 2; 
	data |= pHotStones->placement;
	fwrite(&data, sizeof(unsigned char), 1, pCFile);

	return 1;
}

int readHotStonesFromBFile(FILE* pCFile, HotStones* pHotStones)
{
	unsigned char data = 0;

	fread(&data, sizeof(unsigned char), 1, pCFile);
	pHotStones->type = (data >> 2) & 0x03;
	pHotStones->placement = data & 0x03;

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