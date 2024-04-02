#ifndef _SPA_MANAGEMENT_H
#define _SPA_MANAGEMENT_H

#include "TreatmentManager.h"
#include "RoomManager.h"

//void startTreatment(Treatment* pTreatment, Date date, int hour);
//void endTreatment(Treatment* pTreatment, Date date, int hour);
int addTreatment(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager);
int checkRequirments(TreatmentManager* pTreatmentManager, RoomManager* pRoomManager);

#endif