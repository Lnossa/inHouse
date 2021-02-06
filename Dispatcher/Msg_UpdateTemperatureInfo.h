#pragma once
#include "Msg.h"
#include "Logger/Logger.h"
#include "Dispatcher/Msg_IncomingMQTT.h"


class Msg_UpdateTemperatureInfo : public Msg
{
public:
	Msg_UpdateTemperatureInfo(double temp = -273, double hum = -273, bool isHeating = false);
	
	void fBuildFromMQTTMsg(Msg_IncomingMQTT* pMsg);
	std::shared_ptr<char> fFormatAsJSON();

	double fGetSensorTemperature();
	double fGetSensorHumidity();
	double fGetSetTemperature();
	bool fGetIsHeating();

private:
	double mSensorTemperature;
	double mSensorHumidity;
	double mSetTemperature;
	bool mIsHeating;
};

