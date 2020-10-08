#include "Msg_UpdateWeather.h"


Msg_UpdateWeather::Msg_UpdateWeather(double temp, int icon) : Msg(MsgType_UpdateWeather)
{
	mOutsideTemperature = temp;
	mWeatherIcon = icon;
}

double Msg_UpdateWeather::fGetTemp()
{
	return mOutsideTemperature;
}

int Msg_UpdateWeather::fGetIcon()
{
	return mWeatherIcon;
}