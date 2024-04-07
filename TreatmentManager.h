#ifndef _TREATMENT_MANAGER_H
#define _TREATMENT_MANAGER_H

#include "Treatment.h"
#include "List.h"

typedef struct {
	LIST treatmentList;
	int treatmentCount;
} TreatmentManager;

int			initTreatmentManager(TreatmentManager* pTreatmentManager);
int			addTreatmentToList(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int			revenueFromTreatments(TreatmentManager* pTreatmentManager);
int			paymentForEmployees(TreatmentManager* pTreatmentManager);
int			compareTreatments(const void* treatment1, const void* treatment2);
int			deleteTreatmentFromList(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
int			writeTreatmentManagerToBFile(FILE* pFile, FILE* pCFile, TreatmentManager* pTreatmentManager);
int			readTreatmentManagerFromBFile(FILE* pFile, FILE* pCFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int			writeTreatmentManagerToTextFile(FILE* pFile, TreatmentManager* pTreatmentManager);
int			readTreatmentManagerFromTextFile(FILE* pFile, TreatmentManager* pTreatmentManager, RoomManager* pRoomManager, EmployeeManager* pEmployeeManager);
int			findTreatmentWithRoomAndDate(const TreatmentManager* pTreatmentManager, const Date* pDate, const char* roomCode);
int			findTreatmentWithEmployeeAndDate(const TreatmentManager* pTreatmentManager, const Date* pDate, const int employeeId);
int			deleteTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager);
void		initTreatment(Treatment* pTreatment, TreatmentManager* pTreatmentManager, int option, Room* pRoom, Employee* pEmployee, Date* pDate);
void		printTreatmentList(const TreatmentManager* pTreatmentManager);
void		printTreatmentListWithData(const TreatmentManager* pTreatmentManager);
void		printArrByTreatmentType(const TreatmentManager* pTreatmentManager, int type);
void		updateTreatmenArrUtilitiesStatus(TreatmentManager* pTreatmentManager);
void		freeTreatmentManager(TreatmentManager* pTreatmentManager);
Treatment*	findTreatmentWithCode(const TreatmentManager* pTreatmentManager, const char* treatmentCode);
Treatment*	findTreatmentWithRoom(const TreatmentManager* pTreatmentManager, const char* roomCode);
Treatment*	findTreatmentWithEmployee(const TreatmentManager* pTreatmentManager, const int employeeId);

#endif