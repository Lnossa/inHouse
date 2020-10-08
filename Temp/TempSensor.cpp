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
	if (!fd) init();
	unsigned char buf[4];
	wiringPiI2CWrite(fd, CMD_TEMP);
	delay(100);
	read(fd, buf, 3);
	int temp = (buf[0] << 8 | buf[1]) & 0xFFFC;
	double tSensorTemp = -46.85 + (175.72 * temp / 65536.0);

	return tSensorTemp;
}

double TempSensor::readHumidity()
{
	if (!fd) init();
	unsigned char buf[4];
	wiringPiI2CWrite(fd, CMD_HUM);
	delay(100);
	read(fd, buf, 3);
	int hum = (buf[0] << 8 | buf[1]) & 0xFFFC;
	double tSensorHumidity = -6 + (125 * hum / 65536.0);

	return tSensorHumidity;
}