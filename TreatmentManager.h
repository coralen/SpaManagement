#ifndef _TREATMENT_MANAGER_H
#define _TREATMENT_MANAGER_H

#include "Treatment.h"
#include "List.h"

typedef struct {
	LIST treatmentArr;
	int treatmentCount;
} TreatmentManager;

int			initTreatmentManager(TreatmentManager* pTreatmentManager);
int			addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int			calculateTreatmentsRevenue(TreatmentManager* pTreatmentManager);
int			compareTreatments(const void* treatment1, const void* treatment2);
int			deleteTreatmentFromList(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int			writeTreatmentManagerToBFile(FILE* pFile, TreatmentManager* pTreatmentManager);
int			readTreatmentManagerFromBFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int			writeTreatmentManagerToTextFile(FILE* pFile, TreatmentManager* pTreatmentManager);
int			readTreatmentManagerFromTextFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int			findTreatmentWithRoomAndDate(TreatmentManager* pTreatmentManager, Date* pDate, char* roomCode);
int			findTreatmentWithEmployeeAndDate(TreatmentManager* pTreatmentManager, Date* pDate, int employeeId);
int			deleteTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
void		initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, Employee* pEmployee, Date* pDate);
void		printTreatmentArr(const TreatmentManager* pTreatmentManager);
void		printTreatmentArrWithData(const TreatmentManager* pTreatmentManager);
void		printArrByTreatmentType(const TreatmentManager* pTreatmentManager, int type);
void		updateTreatmenArrUtilitiesStatus(TreatmentManager* pTreatmentManager);
Treatment*	findTreatmentWithCode(TreatmentManager* pTreatmentManager, char* treatmentCode);
Treatment*	findTreatmentWithRoom(TreatmentManager* pTreatmentManager, char* roomCode);
Treatment*	findTreatmentWithEmployee(TreatmentManager* pTreatmentManager, int employeeId);

#endif