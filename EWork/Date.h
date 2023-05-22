#pragma once

#include "stdafx.h"

typedef struct {
	int day, month, year;
}sDate;

class Date
{
	int countLeapYears(sDate date);
public:
	int monthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	bool bGetCurDate = false;

	const char* day_28[28] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
						, "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28" };

	const char* day_29[29] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
						, "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29" };

	const char* day_30[30] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
						, "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30" };

	const char* day_31[31] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
						, "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };

	const char* month[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };
	const char* year[8] = { "2023", "2024", "2025", "2026","2027","2028", "2029","2030" };

	bool isLeapYear(int year);
	int CalcDuration(sDate start, sDate end);
	sDate GetCurrentDate();
	std::string DateToString(sDate date);
	sDate addDays(sDate date, int x);
	bool DateLater(sDate d1, sDate d2);
	int diffDays(const sDate& date1, const sDate& date2);
};

extern Date gDate;