#ifndef _HOT_STONES_H
#define _HOT_STONES_H

#define HOT_STONES_ROOM_TYPE 0
#define HOT_STONES_EMPLOYEE_ROLE 3


typedef enum { eBasalt, eMarble, eHimalayanSalt, eNofStoneType } StonesType;
typedef enum { eBack, eNeck, eHands, eLegs, eNofPlacements } stonePlacement;

typedef struct {
	StonesType type;
	stonePlacement placement;
} HotStones;

int			writeHotStonesToBFileOLD(FILE* pFile, HotStones* pHotStones);
int			readHotStonesFromBFileOLD(FILE* pFile, HotStones* pHotStones);
int			writeHotStonesToBFile(FILE* pCFile, HotStones* pHotStones);
int			readHotStonesFromBFile(FILE* pCFile, HotStones* pHotStones);
int			writeHotStonesToTextFile(FILE* pFile, HotStones* pHotStones);
int			readHotStonesFromTextFile(FILE* pFile, HotStones* pHotStones);
void		getHotStonesType(HotStones* pHotStones);
void		getStonesPlacement(HotStones* pHotStones);
void		printHotStonesType();
void		printHotStonesPlacement();
void		printHotStones(const HotStones* pHotStones);
void		printHotStonesHeaders();
const char* getStonesTypeString(int typeNum);
const char* getStonesPlacementString(int typeNum);

#endif