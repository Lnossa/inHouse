#pragma once
#include "LCD.h"
#include "Utils/Date.h"
#include "Utils/Weather.h"
#include "Dispatcher/Dispatcher.h"
#include "Logger/Logger.h"
#include "Dispatcher/Msg_UpdateSensorTemp.h"
#include "Dispatcher/Msg_UpdateWeather.h"

class LCDManager : public Module
{

public:
	LCDManager();

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;


private:
	std::unique_ptr<LCDDriver> pLCDDriver;
	std::unique_ptr<std::thread> mDateJob;

	void fStartDateJob();
	void fPrintInsideTemp(double temp);
	void fPrintOutsideTemp(double temp, int icon);
};