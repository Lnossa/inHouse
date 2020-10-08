#pragma once



#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <mutex>
#include <wiringPi.h>
#include <wiringPiI2C.h>


#define CMD_RESET 0xFE
#define CMD_TEMP 0xF3
#define CMD_HUM 0xF5

class TempSensor
{
	friend class TemperatureManager;

private:
	int fd;
	void init();

	TempSensor(TempSensor const&) = delete;
	void operator=(TempSensor const&) = delete;

protected:
	TempSensor();
	double readTemperature();
	double readHumidity();
};

