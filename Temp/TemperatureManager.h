#pragma once

#include "TempSensor.h"
#include "Utils/Weather.h"
#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_UpdateSensorTemp.h"
#include "Dispatcher/Msg_UpdateWeather.h"

class TemperatureManager : public Module
{
	
public :
	TemperatureManager();

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;

private:
	double mInsideTemperature;
	double mInsideHumidity;
	double mSetTemperature;

	
	std::unique_ptr<TempSensor> pTempSensor;
	std::unique_ptr<std::thread> mWeatherJob;
	std::unique_ptr<std::thread> mSensorJob;

	void fReadFromSensor();
	
	void fStartWeatherJob();
	void fStartSensorJob();
};

