#pragma once
#include "Msg.h"

class Msg_UpdateWeather : public Msg
{
public:
	Msg_UpdateWeather(double temp, int icon);

	double fGetTemp();
	int fGetIcon();

private:
	double mOutsideTemperature;
	int mWeatherIcon;
};

