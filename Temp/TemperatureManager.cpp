#include <unistd.h>

#include "TemperatureManager.h"

TemperatureManager::TemperatureManager() : Module()
{
	fSetModuleId(Temp);
	pTempSensor = std::unique_ptr<TempSensor>(new TempSensor());
}

void TemperatureManager::fReadFromSensor()
{
	mInsideTemperature = pTempSensor->readTemperature();
	mInsideHumidity = pTempSensor->readHumidity();
}

void TemperatureManager::fOnStart()
{
	mWeatherJob = std::unique_ptr<std::thread>(new std::thread(&TemperatureManager::fStartWeatherJob, this));
	mSensorJob = std::unique_ptr<std::thread>(new std::thread(&TemperatureManager::fStartSensorJob, this));	
}

void TemperatureManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	std::cout << "TemperatureManager process message." << std::endl;
}


void TemperatureManager::fStartWeatherJob()
{
	logging::TRACE("TemperatureManager >> Started weather job.");
	Weather w;
	while (true)
	{
		w.fUpdateWeather();
		if (w.fGetCurTemp() != -273)
		{
			Msg_UpdateWeather msg(w.fGetCurTemp(), w.fGetIcon());
			auto spMsg = std::make_shared<Msg_UpdateWeather>(msg);
			gpDispatcher->fPostMessage(Module::Id::LCD, spMsg);
		}
		else
		{
			std::cout << "Weather error" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::hours(1));
	}

}

void TemperatureManager::fStartSensorJob()
{
	logging::TRACE("TemperatureManager >> Started sensor job.");
	while (true)
	{
		fReadFromSensor();
		logging::TRACE("TemperatureManager >> Read from sensor: Temp: %.1f Humidity: %.1f", mInsideTemperature, mInsideHumidity);
		Msg_UpdateSensorTemp msg(mInsideTemperature, mInsideHumidity);
		auto spMsg = std::make_shared<Msg_UpdateSensorTemp>(msg);
		gpDispatcher->fPostMessage(Module::Id::LCD, spMsg);
		gpDispatcher->fPostMessage(MQTT, spMsg);
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}
}