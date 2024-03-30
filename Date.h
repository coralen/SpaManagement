#ifndef _DATE_H
#define _DATE_H

#include "Helper.h"

#define MIN_DAY 1
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_YEAR 2023
#define SEGMENTS 3
#define CHARS_COUNT 12

#define CLOCK_FORMAT "24H"

typedef struct {
	int hour;
	int day;
	int month;
	int year;
} Date;

void getCorrectDate(Date* pDate);
void getCorrentHour(Date* pDate);
void printDate(const Date* pdate);
int validateDate(const int day, const int month, const int year);


#endif
