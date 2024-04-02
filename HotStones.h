#ifndef _HOTSTONES_H
#define _HOTSTONES_H

#define HOT_STONES_ROOM_TYPE 0
#define HOT_STONES_TYPE_COUNT 3
#define HOT_STONES_PLACEMENT_COUNT 4

static const char* stonesTypeString[HOT_STONES_TYPE_COUNT] = { "Basalt", "Marble" ,"Himalayan Salt" };
static const char* stonesPlacementString[HOT_STONES_PLACEMENT_COUNT] = { "Back", "Neck" ,"Hands", "Legs" };


typedef enum { BASALT, MARBLE , HIMALAYAN_SALT } StonesType;
typedef enum { BACK, NECK, HANDS, LEGS } stonePlacement;
 
typedef struct {
	StonesType sType;
	stonePlacement sPlacement;
} HotStones;

void	getHotStonesType(HotStones* pHotStones);
void	getStonesPlacement(HotStones* pHotStones);
void	printHotStonesType();
void	printHotStonesPlacement();
#endif