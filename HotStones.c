#include <stdio.h>
#include "HotStones.h"

/* implement
*  getHotStonesType(&pTreatment->data.hotStones.sType);
*  getStonesPlacement(&pTreatment->data.hotStones.sPlacement);
*/

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
		printf("%d - %s\n", i + 1, stonesTypeString[i]);
}

void printHotStonesPlacement()
{
	for (int i = 0; i < HOT_STONES_PLACEMENT_COUNT; i++)
		printf("%d - %s\n", i + 1, stonesPlacementString[i]);
}
