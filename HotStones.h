#ifndef _HOT_STONES_H
#define _HOT_STONES_H

#define HOT_STONES_ROOM_TYPE 0
#define HOT_STONES_TYPE_COUNT 3
#define HOT_STONES_PLACEMENT_COUNT 4

typedef enum { BASALT, MARBLE , HIMALAYAN_SALT } StonesType;
typedef enum { BACK, NECK, HANDS, LEGS } stonePlacement;
 
typedef struct {
	StonesType sType;
	stonePlacement sPlacement;
} HotStones;

void		getHotStonesType(HotStones* pHotStones);
void		getStonesPlacement(HotStones* pHotStones);
void		printHotStonesType();
void		printHotStonesPlacement();
const char*	getStonesTypeString(int typeNum);
const char*	getStonesPlacementString(int typeNum);

#endif