#include "Date.h"
#include <iostream>

Date::Date()
{
	time_t now = time(0);
	mTime = localtime(&now);

	mYear = mTime->tm_year + 1900;
	mMonth = 1 + mTime->tm_mon;
	mDay = mTime->tm_mday;

	mHour = mTime->tm_hour;
	mMinute = mTime->tm_min;
	mSec = mTime->tm_sec;

	mWeekDay = mTime->tm_wday;
}

tm* Date::fGetTime()
{
	return mTime;
}

int Date::fGetYear()
{
	return mYear;
}

int Date::fGetMonth()
{
	return mMonth;
}

int Date::fGetDay()
{
	return mDay;
}

int Date::fGetHour()
{
	return mHour;
}

int Date::fGetMinute()
{
	return mMinute;
}

int Date::fGetSecond()
{
	return mSec;
}

int Date::fGetWeekDay()
{
	return mWeekDay;
}


std::string Date::fGetMonthString()
{
	std::string sM;
	switch (mMonth)
	{
	case 1:
		sM = "Jan";
		break;
	case 2:
		sM = "Feb";
		break;
	case 3:
		sM = "Mar";
		break;
	case 4:
		sM = "Apr";
		break;
	case 5:
		sM = "May";
		break;
	case 6:
		sM = "Jun";
		break;
	case 7:
		sM = "Jul";
		break;
	case 8:
		sM = "Aug";
		break;
	case 9:
		sM = "Sep";
		break;
	case 10:
		sM = "Oct";
		break;
	case 11:
		sM = "Nov";
		break;
	case 12:
		sM = "Dec";
		break;
	default:
		break;
	}
	return sM;
}

std::string Date::fGetWeekDayString()
{
	std::string sWD;
	switch (mWeekDay)
	{
	case 0:
		sWD = "Sun";
		break;
	case 1:
		sWD = "Mon";
		break;
	case 2:
		sWD = "Tue";
		break;
	case 3:
		sWD = "Wed";
		break;
	case 4:
		sWD = "Thu";
		break;
	case 5:
		sWD = "Fri";
		break;
	case 6:
		sWD = "Sat";
		break;
	}

	return sWD;
}

std::string Date::fGetTimeAndDateString()
{
	char buffer[17];
	std::string sWD = fGetWeekDayString();
	std::string sM = fGetMonthString();
	snprintf(buffer, 17, "%s %02d %s %02d:%02d", sWD.c_str(), mDay, sM.c_str(), mHour, mMinute);
	std::string returnStr(buffer);
	return returnStr.c_str();
}