#include "Msg_UpdateSensorTemp.h"


Msg_UpdateSensorTemp::Msg_UpdateSensorTemp(double temp, double hum)
	: Msg(MsgType::MsgType_UpdateSensorTemp)
{
	mTemp = temp;
	mHumidity = hum;
}

double Msg_UpdateSensorTemp::getTemperature()
{
	return mTemp;
}

double Msg_UpdateSensorTemp::getHumidity()
{
	return mHumidity;
}