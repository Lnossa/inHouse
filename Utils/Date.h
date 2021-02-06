#pragma once
#include<string>

class Date
{
private:
	tm* mTime;
	int mYear;
	int mMonth;
	int mDay;
	int mHour;
	int mMinute;
	int mSec;
	int mWeekDay;

public:
	Date();

	tm* fGetTime();
	int fGetYear();
	int fGetMonth();
	int fGetDay();
	int fGetHour();
	int fGetMinute();
	int fGetSecond();
	int fGetWeekDay();

	std::string fGetMonthString();
	std::string fGetWeekDayString();
	std::string fGetTimeAndDateString();

};

