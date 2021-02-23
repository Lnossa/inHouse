#pragma once
#include "LCD.h"
#include "Utils/Date.h"
#include "Logger/Logger.h"
#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_UpdateWeather.h"
#include "Dispatcher/Msg_UpdateTemperatureInfo.h"

class LCDManager : public Module
{

public:
	LCDManager();

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;
	void fOnStop() override;


private:
	void fStartDateJob();
	void fPrintInsideTemp(double temp);
	void fPrintOutsideTemp(double temp, int icon);

	std::unique_ptr<LCDDriver> pLCDDriver;
	std::unique_ptr<std::thread> mDateJob;
};