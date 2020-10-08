#pragma once
#include "Msg.h"


class Msg_UpdateSensorTemp : public Msg
{
public:
	Msg_UpdateSensorTemp(double temp, double hum);
	
	double getTemperature();
	double getHumidity();

private:
	double mTemp;
	double mHumidity;
};

