#pragma once

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

#include "HTTP.h"
#include "Date.h"

class Weather
{
private:
	int mCurTemp;
	int mMaxTemp;
	int mMinTemp;
	int mIcon;
	std::string mText;
	
	std::string fQueryCurrent();
	std::string fQueryForecast();
public:
	Weather();
	void fUpdateWeather();

	int fGetCurTemp();
	int fGetMaxTemp();
	int fGetMinTemp();
	int fGetIcon();
};

