#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "Helper.h"

#include "SpaManagement.h"

int menu();

int main()
{
	TreatmentManager tManager;
	RoomManager rManager;
	addTreatment(&tManager, &rManager);
	return 1;
}

int menu()
{
	return 1;
}