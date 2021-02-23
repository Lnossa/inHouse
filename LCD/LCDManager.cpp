#include "LCDManager.h"

LCDManager::LCDManager() : Module()
{
	fSetModuleId(LCD);
	pLCDDriver =  std::unique_ptr<LCDDriver>(new LCDDriver);
	pLCDDriver->lcdInit();
}

void LCDManager::fOnStart()
{
	mDateJob = std::unique_ptr<std::thread>(new std::thread(&LCDManager::fStartDateJob, this));
}

void LCDManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	logging::INFO("LCDManager >> Received %s.", msg->fGetTypeAsString());
	switch (msg->fGetType())
	{
	case MsgType_UpdateTemperatureInfo:
	{
		Msg_UpdateTemperatureInfo* pMsg = static_cast<Msg_UpdateTemperatureInfo*>(msg.get());
		logging::TRACE("LCDManager >> Received: sensor temp: %.1f hum: %.1f", pMsg->fGetTypeAsString(), pMsg->fGetSensorTemperature(), pMsg->fGetSensorHumidity());
		fPrintInsideTemp(pMsg->fGetSensorTemperature());
		break;
	}
	case MsgType_UpdateWeather:
	{
		Msg_UpdateWeather* pMsg = static_cast<Msg_UpdateWeather*>(msg.get());
		logging::TRACE("LCDManager >> Received: weather temp: %.1f, icon: %d", pMsg->fGetTemp(), pMsg->fGetIcon());
		fPrintOutsideTemp(pMsg->fGetTemp(), pMsg->fGetIcon());
		break;
	}
	case MsgType_Undefined:
		logging::WARN("Undefined message!");
		break;

	default:

		logging::WARN("Unexpected message!");
		break;
	}
}

void LCDManager::fOnStop()
{
	fStopChildThreads();
	mDateJob->join();
	gpDispatcher->fUnregisterThread(this);
}


void LCDManager::fStartDateJob() 
{
	logging::TRACE("LCDManager >> DateJob || Start");
	while (!fGetShouldExit())
	{
		Date dt;
		logging::TRACE("LCDManager >> DateJob || Update time: %s", dt.fGetTimeAndDateString().c_str());
		pLCDDriver->Lock();
		pLCDDriver->lcdSetPosition(0, 1);
		pLCDDriver->lcdPuts(dt.fGetTimeAndDateString().c_str());
		pLCDDriver->Unlock();

		//ms to delay until next minute
		int delayMs = (60 - dt.fGetSecond()) * 1000;

		fInteruptibleWait(delayMs);
	}
	logging::TRACE("LCDManager >> DateJob || Stopped");
}

void LCDManager::fPrintInsideTemp(double temp)
{
	pLCDDriver->Lock();
	pLCDDriver->lcdSetPosition(0, 0);
	pLCDDriver->lcdPrintf("In:%.1f", temp);
	pLCDDriver->Unlock();
}

void LCDManager::fPrintOutsideTemp(double temp, int icon)
{
	pLCDDriver->Lock();
	//temp
	pLCDDriver->lcdSetPosition(8, 0);
	pLCDDriver->lcdPrintf("Out:%.0f", temp);

	//icon
	pLCDDriver->lcdSetPosition(15, 0);
	int lcdChar = icon < 6 ? LCD_CHR_SUN :
		icon < 12 ? LCD_CHR_CLOUD :
		icon < 30 ? LCD_CHR_RAIN :
		icon < 35 ? LCD_CHR_SUN :
		icon < 39 ? LCD_CHR_CLOUD : LCD_CHR_RAIN;
	pLCDDriver->lcdPrintCustomChar(lcdChar);
	pLCDDriver->Unlock();
}