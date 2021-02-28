#include "Weather.h"

Weather::Weather() 
{
	mCurTemp = -273;
	mMinTemp = -273;
	mMaxTemp = -273;
	mIcon = -1;
}
// SH - 1869987
// BV - 287345

std::string Weather::fQueryCurrent()
{
	return HTTP::GET(
		"http://dataservice.accuweather.com/currentconditions/v1/1869987?apikey=zt5pWPCZDXJTACHKYAw5mCgjicOVlzJW"
	);
}

std::string Weather::fQueryForecast()
{
	return HTTP::GET(
		"http://dataservice.accuweather.com/forecasts/v1/daily/1day/1869987?apikey=zt5pWPCZDXJTACHKYAw5mCgjicOVlzJW&metric=true"
	);
}

void Weather::fUpdateWeather()
{
	Json::Reader reader;
	Json::Value current;
	Json::Value forecast;
	std::string sCurrentJson = "";
	std::string sForecastJson = "";

	Date* dt = new Date();
	int hour = dt->fGetHour();
	delete dt;

	if (mIcon == -1 || hour == 6 || hour == 13 || hour == 20)
	{
		sForecastJson = fQueryForecast();
		if (sForecastJson.length() > 0)
		{
			try 
			{
				reader.parse(sForecastJson, forecast);
				mMaxTemp = forecast["DailyForecasts"][0]["Temperature"]["Maximum"]["Value"].asInt();
				mMinTemp = forecast["DailyForecasts"][0]["Temperature"]["Minimum"]["Value"].asInt();
				mIcon = hour < 20 ?
					forecast["DailyForecasts"][0]["Day"]["Icon"].asInt() :
					forecast["DailyForecasts"][0]["Night"]["Icon"].asInt();
			}
			catch(int e)
			{
				
			}
		}
	}

	sCurrentJson = fQueryCurrent();
	if (sCurrentJson.length() > 0 )
	{
		try
		{
			reader.parse(sCurrentJson, current);
			mCurTemp = current[0]["Temperature"]["Metric"]["Value"].asInt();
		}
		catch (int e)
		{

		}
	}

}

int Weather::fGetCurTemp()
{
	return mCurTemp;
}

int Weather::fGetMaxTemp()
{
	return mMaxTemp;
}

int Weather::fGetMinTemp()
{
	return mMinTemp;
}

int Weather::fGetIcon()
{
	return mIcon;
}

