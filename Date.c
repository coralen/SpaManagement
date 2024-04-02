#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Date.h"


static const int max_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void getCorrectDate(Date* pDate)
{
	char date[MAX_STRING];
	int count, validInputFlag = 0, day = 0, month = 0, year = 0;

	while (!validInputFlag)
	{
		printf("Enter treatment Date dd##mm##yyyy  minimum year %d\n", MIN_YEAR);
		scanf("%s", date);
		count = sscanf(date, "%2d##%2d##%4d", &day, &month, &year);

		if (count != SEGMENTS || strlen(date) != CHARS_COUNT || !validateDate(day, month, year)) {
			printf("Error try again\n");
			validInputFlag = 0;
		}
		else validInputFlag = 1;
	}

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;
}

void getCorrentHour(Date* pDate)
{
	int hour, validInputFlag = 0;

	while (!validInputFlag)
	{
		printf("Enter treatment hour in %s:\n", CLOCK_FORMAT);
		scanf("%d", &hour);
		if (hour < 0 && hour > 23) printf("Error, please try again\n");
		else validInputFlag = 1;
	}
	pDate->hour = hour;
}

void printDate(const Date* pdate)
{
	printf("Date: %d/%d/%d", pdate->day, pdate->month, pdate->year);
}

int validateDate(const int day, const int month, const int year)
{
	if (day < MIN_DAY || day > max_days[month - 1]) return 0;
	if (month < MIN_MONTH || month > MAX_MONTH || year < MIN_YEAR) return 0;

	return 1;
}
