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
	case MsgType_UpdateSensorTemp:
	{
		Msg_UpdateSensorTemp* pMsg = static_cast<Msg_UpdateSensorTemp*>(msg.get());
		logging::TRACE("LCDManager >> Sensor: Temp: %.1f Hum: %.1f", pMsg->fGetTypeAsString(), pMsg->getTemperature(), pMsg->getHumidity());
		fPrintInsideTemp(pMsg->getTemperature());
		break;
	}
	case MsgType_UpdateWeather:
	{
		Msg_UpdateWeather* pMsg = static_cast<Msg_UpdateWeather*>(msg.get());
		logging::TRACE("LCDManager >> Weather: Temp: %.1f, Icon: %d", pMsg->fGetTemp(), pMsg->fGetIcon());
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


void LCDManager::fStartDateJob() 
{
	while (true)
	{
		Date* dt = new Date();
		
		pLCDDriver->mMutex.lock();
		pLCDDriver->lcdSetPosition(0, 1);
		pLCDDriver->lcdPuts(dt->fGetTimeAndDateString().c_str());
		pLCDDriver->mMutex.unlock();
		
		//ms to delay until next minute
		int delayMs = (60 - dt->fGetSecond()) * 1000;

		delete dt;
		delay(delayMs);
	}
}

//
//void TemperatureManager::fStartWeatherJob()
//{
//	Weather w;
//	while (true)
//	{
//		w.fUpdateWeather();
//		pLCDDriver->mMutex.lock();
//		pLCDDriver->lcdSetPosition(0, 0);
//		if (w.fGetCurTemp() != -273)
//		{
//			pLCDDriver->lcdPrintf("Out:%02dC(%02d-%02d)", w.fGetCurTemp(), w.fGetMinTemp(), w.fGetMaxTemp());
//			pLCDDriver->lcdSetPosition(15, 0);
//			int icon = w.fGetIcon();
//			int lcdChar = icon < 6 ? LCD_CHR_SUN :
//				icon < 12 ? LCD_CHR_CLOUD :
//				icon < 30 ? LCD_CHR_RAIN :
//				icon < 35 ? LCD_CHR_SUN :
//				icon < 39 ? LCD_CHR_CLOUD : LCD_CHR_RAIN;
//			pLCDDriver->lcdPrintCustomChar(lcdChar);
//		}
//		else
//		{
//			pLCDDriver->lcdPrintf("Weather error");
//		}
//
//		pLCDDriver->mMutex.unlock();
//		delay(3600000);
//	}
//
//}

void LCDManager::fPrintInsideTemp(double temp)
{
	pLCDDriver->mMutex.lock();
	pLCDDriver->lcdSetPosition(0, 0);
	pLCDDriver->lcdPrintf("In:%.1f", temp);
	pLCDDriver->mMutex.unlock();
}

void LCDManager::fPrintOutsideTemp(double temp, int icon)
{
	pLCDDriver->mMutex.lock();
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
	pLCDDriver->mMutex.unlock();
}