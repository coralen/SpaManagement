#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Date.h"


static const int max_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void getCorrectDate(Date* pDate)
{
	char date[MAX_STRING];
	int count, validInputFlag = 0, day = 0, month = 0, year = 0;

	while (!validInputFlag)
	{
		printf("Enter treatment date in the format dd##mm##yyyy for future time, later than the current hour:\n");
		scanf(SCANF_FORMAT, date);
		while (getchar() != '\n');
		date[MAX_STRING - 1] = '\0';

		count = sscanf(date, "%2d##%2d##%4d", &day, &month, &year);

		if (count != SEGMENTS || strlen(date) != CHARS_COUNT || !validateDate(day, month, year)) {
			printf("Invalid date format or date out of range. Please try again\n");
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
		if (hour < 0 || hour > 23) printf("Error, please try again\n");
		else validInputFlag = 1;
	}
	pDate->hour = hour;
}

void printDate(const Date* pdate)
{
	printf("%d/%d/%d\t", pdate->day, pdate->month, pdate->year);
}

int validateDate(const int day, const int month, const int year)
{
	if (day < MIN_DAY || day > max_days[month - 1]) return 0;
	if (month < MIN_MONTH || month > MAX_MONTH || year < MIN_YEAR) return 0;

	return 1;
}

int writeDateToTextFile(FILE* pFile, const Date* pDate)
{
	if (fprintf(pFile, "%d##%d##%d:%d\n", pDate->day, pDate->month, pDate->year, pDate->hour) < 0) return 0;
	return 1;
}

int readDateFromTextFile(FILE* pFile, Date* pDate)
{
	if (!fscanf(pFile, "%d##%d##%d:%d\n", &pDate->day, &pDate->month, &pDate->year, &pDate->hour)) return 0;
	return 1;
}

time_t convertToTimeT(const Date* pDate)
{
	struct tm timeStruct = { 0 };

	timeStruct.tm_year = pDate->year - 1900;
	timeStruct.tm_mon = pDate->month - 1;
	timeStruct.tm_mday = pDate->day;
	timeStruct.tm_hour = pDate->hour;
	timeStruct.tm_min = 0;
	timeStruct.tm_sec = 0;
	timeStruct.tm_isdst = -1;
	time_t time = mktime(&timeStruct);

	return time;
}


int compareDates(const Date* pDate1, const Date* pDate2) 
{
	if (pDate1->year != pDate2->year)
		return pDate1->year - pDate2->year;
	if (pDate1->month != pDate2->month)
		return pDate1->month - pDate2->month;
	if (pDate1->day != pDate2->day)
		return pDate1->day - pDate2->day;
	return pDate1->hour - pDate2->hour;
}

int isDateRelevant(const Date* pDate)
{
	Date tmpDate = *pDate;
	time_t currentTime = time(NULL);
	time_t treatmentTime = convertToTimeT(&tmpDate);

	if (difftime(currentTime, treatmentTime) > 0) return 0;
	return 1;
}