#pragma once

#include "TempSensor.h"
#include "Utils/Weather.h"
#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_UpdateTemperatureInfo.h"
#include "Dispatcher/Msg_UpdateWeather.h"

class TemperatureManager : public Module
{
	
public :
	TemperatureManager();

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;
	void fOnStop() override;

private:
	bool mIsHeating;
	double mInsideTemperature;
	double mInsideHumidity;
	double mSetTemperature;

	bool mKeepJobsAlive;
	std::unique_ptr<TempSensor> pTempSensor;
	std::unique_ptr<std::thread> mWeatherJob;
	std::unique_ptr<std::thread> mTemperatureJob;

	bool fCheckTemp();
	void fReadFromSensor();
	
	void fStartWeatherJob();
	void fStartTemperatureJob();

};

