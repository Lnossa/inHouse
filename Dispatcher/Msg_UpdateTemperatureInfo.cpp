#include "Msg_UpdateTemperatureInfo.h"


Msg_UpdateTemperatureInfo::Msg_UpdateTemperatureInfo(double temp, double hum, bool isHeating)
	: Msg(MsgType::MsgType_UpdateTemperatureInfo),
	mSensorTemperature(temp),
	mSensorHumidity(hum),
	mSetTemperature(-275),
	mIsHeating(isHeating)
{
}

double Msg_UpdateTemperatureInfo::fGetSensorTemperature()
{
	return mSensorTemperature;
}

double Msg_UpdateTemperatureInfo::fGetSensorHumidity()
{
	return mSensorHumidity;
}

double Msg_UpdateTemperatureInfo::fGetSetTemperature()
{
	return mSetTemperature;
}

bool Msg_UpdateTemperatureInfo::fGetIsHeating()
{
	return mIsHeating;
}

void Msg_UpdateTemperatureInfo::fBuildFromMQTTMsg(Msg_IncomingMQTT* pMsg)
{
	std::string msgData = pMsg->fGetMessage();
	mSetTemperature = std::stoi(msgData.c_str());
}

std::shared_ptr<char> Msg_UpdateTemperatureInfo::fFormatAsJSON()
{
	size_t size = snprintf(nullptr, 0, "{\"Temp\":\"%.1f\", \"Hum\":\"%.1f\", \"Heat\":\"%s\"}", mSensorTemperature, mSensorHumidity, mIsHeating ? "ON" : "OFF" ) + 1; // Extra space for '\0'
	if (size > 0) { 
		std::shared_ptr<char> str(new char[size]);
		snprintf(str.get(), size, "{\"Temp\":\"%.1f\", \"Hum\":\"%.1f\", \"Heat\":\"%s\"}", mSensorTemperature, mSensorHumidity, mIsHeating ? "ON" : "OFF");
		return str;
	}
	logging::ERROR("Json format error!");
	return NULL;
}