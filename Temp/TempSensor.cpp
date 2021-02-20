#include "TempSensor.h"


TempSensor::TempSensor() 
{
	init();
}

void TempSensor::init()
{
	fd = wiringPiI2CSetup(0x40);
	if (fd >= 0)
	{
		wiringPiI2CWrite(fd, CMD_RESET);
		delay(15);
	}
}


double TempSensor::readTemperature()
{
	double tSensorTemp = -275.15;
	if (!fd) init();
	unsigned char buf[4];
	wiringPiI2CWrite(fd, CMD_TEMP);
	delay(100);
	if (read(fd, buf, 3) > 0)
	{
		int temp = (buf[0] << 8 | buf[1]) & 0xFFFC;
		tSensorTemp = -46.85 + (175.72 * temp / 65536.0);
	}

	return tSensorTemp;
}

double TempSensor::readHumidity()
{
	double tSensorHumidity = -1;
	if (!fd) init();
	unsigned char buf[4];
	wiringPiI2CWrite(fd, CMD_HUM);
	delay(100);
	if (read(fd, buf, 3) > 0)
	{
		int hum = (buf[0] << 8 | buf[1]) & 0xFFFC;
		tSensorHumidity = -6 + (125 * hum / 65536.0);
	}

	return tSensorHumidity;
}