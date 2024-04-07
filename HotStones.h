#ifndef _HOT_STONES_H
#define _HOT_STONES_H

#define HOT_STONES_ROOM_TYPE 0
#define HOT_STONES_EMPLOYEE_ROLE 3


typedef enum { eBasalt, eMarble, eHimalayanSalt, eNofStoneType } StonesType;
typedef enum { eBack, eNeck, eHands, eLegs, eNofPlacements } StonePlacement;

typedef struct {
	StonesType type;
	StonePlacement placement;
} HotStones;

int			writeHotStonesToBFile(FILE* pCFile, const HotStones* pHotStones);
int			readHotStonesFromBFile(FILE* pCFile, HotStones* pHotStones);
int			writeHotStonesToTextFile(FILE* pFile, const HotStones* pHotStones);
int			readHotStonesFromTextFile(FILE* pFile, HotStones* pHotStones);
void		getHotStonesType(HotStones* pHotStones);
void		getStonesPlacement(HotStones* pHotStones);
void		printHotStonesType();
void		printHotStonesPlacement();
void		printHotStones(const HotStones* pHotStones);
void		printHotStonesHeaders(void* input);
const char* getStonesTypeString(const int typeNum);
const char* getStonesPlacementString(const int typeNum);

#endif