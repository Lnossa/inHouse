#include <unistd.h>

#include "TemperatureManager.h"

TemperatureManager::TemperatureManager() :
	Module(),
	mIsHeating(false),
	mInsideTemperature(-273),
	mInsideHumidity(0),
	mSetTemperature(-273),
	mKeepJobsAlive(true)
{
	fSetModuleId(Temp);
	pTempSensor = std::unique_ptr<TempSensor>(new TempSensor());
}



void TemperatureManager::fOnStart()
{
	mWeatherJob = std::unique_ptr<std::thread>(new std::thread(&TemperatureManager::fStartWeatherJob, this));
	mTemperatureJob = std::unique_ptr<std::thread>(new std::thread(&TemperatureManager::fStartTemperatureJob, this));	
}

void TemperatureManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	logging::INFO("TemperatureManager >> Received %s.", msg->fGetTypeAsString());
	switch (msg->fGetType())
	{
	case MsgType_UpdateTemperatureInfo:
	{
		Msg_UpdateTemperatureInfo* pMsg = static_cast<Msg_UpdateTemperatureInfo*>(msg.get());
		mSetTemperature = pMsg->fGetSetTemperature();
		fCheckTemp();
		break;
	}
	default:
		logging::WARN("Unexpected message!");
		break;
	}

}

void TemperatureManager::fOnStop()
{
	fStopChildThreads();
	mTemperatureJob->join();
	gpDispatcher->fUnregisterThread(this);
}

bool TemperatureManager::fCheckTemp()
{
	double hysteresis = 1.5;
	if (mSetTemperature != -273 && mInsideTemperature != -273)
	{
		if (mIsHeating)
		{
			if (mInsideTemperature < mSetTemperature + (hysteresis / 2))
			{
				logging::DEBUG("TemperatureManager >> Temperature Job || Heating ON -> ON. Temp: %.1f Set: %.1f", mInsideTemperature, mSetTemperature);
				//turn heating on
				mIsHeating = true;
			}
			else
			{
				logging::INFO("TemperatureManager >> Temperature Job || Heating ON -> OFF. Temp: %.1f Set: %.1f", mInsideTemperature, mSetTemperature);
				//turn heating off
				mIsHeating = false;
			}
		}
		else
		{
			if (mInsideTemperature < mSetTemperature - (hysteresis / 2))
			{
				logging::INFO("TemperatureManager >> Temperature Job || Heating OFF -> ON. Temp: %.1f Set: %.1f", mInsideTemperature, mSetTemperature);
				Msg_UpdateTemperatureInfo msg(mInsideTemperature, mInsideHumidity, mIsHeating);
				auto spMsg = std::make_shared<Msg_UpdateTemperatureInfo>(msg);
				gpDispatcher->fPostMessage(MQTT, spMsg);
				mIsHeating = true;
			}
			else
			{
				logging::DEBUG("TemperatureManager >> Temperature Job || Heating OFF -> OFF. Temp: %.1f Set: %.1f", mInsideTemperature, mSetTemperature);
				//turn heating off
				mIsHeating = false;
			}
		}
		return true;
	}
	else
	{
		logging::WARN("TemperatureManager >> Temperature Job || Temps not set!");
		return false;
	}
}

void TemperatureManager::fReadFromSensor()
{
	mInsideTemperature = pTempSensor->readTemperature();
	mInsideHumidity = pTempSensor->readHumidity();
	logging::TRACE("TemperatureManager >> Read from sensor: Temp: %.1f Humidity: %.1f", mInsideTemperature, mInsideHumidity);
}

void TemperatureManager::fStartWeatherJob()
{
	logging::TRACE("TemperatureManager >> Started weather job.");
	Weather w;
	while (!fGetShouldExit())
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
		fInteruptibleWait(1000 * 3600); //1 hour
	}
	logging::TRACE("TemperatureManager >> Stopped weather job.");
}

void TemperatureManager::fStartTemperatureJob()
{
	logging::TRACE("TemperatureManager >> Started sensor job.");
	while (!fGetShouldExit())
	{
		unsigned int wait = 10;
		fReadFromSensor();
		if (!fCheckTemp())
		{
			wait = 1;
		}
		Msg_UpdateTemperatureInfo msg(mInsideTemperature, mInsideHumidity, mIsHeating);
		auto spMsg = std::make_shared<Msg_UpdateTemperatureInfo>(msg);
		gpDispatcher->fPostMessage(Module::Id::LCD, spMsg);
		gpDispatcher->fPostMessage(MQTT, spMsg);
		fInteruptibleWait(wait * 1000 * 60); //minutes
	}
	logging::TRACE("TemperatureManager >> Stopped sensor job.");
}
