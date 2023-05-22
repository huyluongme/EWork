#include "stdafx.h"
#include "Date.h"


Date gDate;

bool Date::isLeapYear(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int Date::countLeapYears(sDate date) {
	int years = date.year;

	// Check if the current year needs to be
	//  considered for the count of leap years
	// or not
	if (date.month <= 2)
		years--;

	// An year is a leap year if it 
	// is a multiple of 4,
	// multiple of 400 and not a 
	// multiple of 100.
	return years / 4
		- years / 100
		+ years / 400;
}

int Date::CalcDuration(sDate start, sDate end) {
	// COUNT TOTAL NUMBER OF DAYS
	// BEFORE FIRST DATE 'dt1'

	// initialize count using years and day
	int n1 = start.year * 365 + start.day;

	// Add days for months in given date
	for (int i = 0; i < start.month - 1; i++)
		n1 += monthDays[i];

	// Since every leap year is of 366 days,
	// Add a day for every leap year
	n1 += countLeapYears(start);

	// SIMILARLY, COUNT TOTAL NUMBER OF
	// DAYS BEFORE 'dt2'

	int n2 = end.year * 365 + end.day;
	for (int i = 0; i < end.month - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(end);

	// return difference between two counts
	return (n2 - n1);
}

sDate Date::GetCurrentDate() {
	// Get current time
	auto now = std::chrono::system_clock::now();

	// Convert current time to time_t
	std::time_t now_time = std::chrono::system_clock::to_time_t(now);

	// Convert time_t to tm structure
	std::tm* now_tm = std::localtime(&now_time);

	sDate cur_date{ now_tm->tm_mday, now_tm->tm_mon + 1, now_tm->tm_year + 1900 };
	return cur_date;
}

std::string Date::DateToString(sDate date) {
	return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
}

// Return if year is leap year or not.
bool isLeap(int y)
{
    if (y % 100 != 0 && y % 4 == 0 || y % 400 == 0)
        return true;

    return false;
}

// Given a date, returns number of days elapsed
// from the  beginning of the current year (1st
// jan).
int offsetDays(int d, int m, int y)
{
    int offset = d;

    switch (m - 1)
    {
    case 11:
        offset += 30;
    case 10:
        offset += 31;
    case 9:
        offset += 30;
    case 8:
        offset += 31;
    case 7:
        offset += 31;
    case 6:
        offset += 30;
    case 5:
        offset += 31;
    case 4:
        offset += 30;
    case 3:
        offset += 31;
    case 2:
        offset += 28;
    case 1:
        offset += 31;
    }

    if (isLeap(y) && m > 2)
        offset += 1;

    return offset;
}

// Given a year and days elapsed in it, finds
// date by storing results in d and m.
void revoffsetDays(int offset, sDate* date)
{
    int month[13] = { 0, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31 };

    if (isLeap(date->year))
        month[2] = 29;

    int i;
    for (i = 1; i <= 12; i++)
    {
        if (offset <= month[i])
            break;
        offset = offset - month[i];
    }

    date->day = offset;
    date->month = i;
}

// Add x days to the given date.
sDate Date::addDays(sDate date, int x)
{
    int offset1 = offsetDays(date.day, date.month, date.year);
    int remDays = isLeap(date.year) ? (366 - offset1) : (365 - offset1);

    // y2 is going to store result year and
    // offset2 is going to store offset days
    // in result year.
    sDate res;
    int offset2;
    if (x <= remDays)
    {
        res.year = date.year;
        offset2 = offset1 + x;
    }

    else
    {
        // x may store thousands of days.
        // We find correct year and offset
        // in the year.
        x -= remDays;
        res.year = date.year + 1;
        int y2days = isLeap(res.year) ? 366 : 365;
        while (x >= y2days)
        {
            x -= y2days;
            res.year++;
            y2days = isLeap(res.year) ? 366 : 365;
        }
        offset2 = x;
    }

    // Find values of day and month from
    // offset of result year.
    int m2, d2;
    revoffsetDays(offset2, &res);

    return res;
}

bool Date::DateLater(sDate d1, sDate d2) {
    if (d1.year != d2.year) {
        return d1.year > d2.year;
    }
    if (d1.month != d2.month) {
        return d1.month > d2.month;
    }
    return d1.day > d2.day;
}

int Date::diffDays(const sDate& date1, const sDate& date2)
{
    int offset1 = offsetDays(date1.day, date1.month, date1.year);
    int offset2 = offsetDays(date2.day, date2.month, date2.year);

    int diff = offset2 - offset1;
    if (date2.year > date1.year && isLeap(date1.year) && date1.month <= 2 && date2.month > 2)
        diff--;

    return diff;
}