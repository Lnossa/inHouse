#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "TempSensor.h"
#include "TemperatureManager.h"
int main()
{
	//double temp = TempSensor::fGetSensorTemperature();
	//double hum = TempSensor::fGetSensorHumidity();

	//std::cout << "Temp: " << std::fixed << std::setprecision(1) << temp << std::endl;
	//std::cout << "Humidity: " << hum << "%" << std::endl;

	//TemperatureManager::start();

	return 0;
}

//double getTemp(int fd) 
//{
//	unsigned char buf[4];
//	wiringPiI2CWrite(fd, CMD_TEMP);
//	delay(100);
//	read(fd, buf, 3);
//	int temp = (buf[0] << 8 | buf[1]) & 0xFFFC;
//	double tSensorTemp = -46.85 + (175.72 * temp / 65536.0);
//
//	return tSensorTemp;
//}
//
//double fGetSensorHumidity(int fd)
//{
//	unsigned char buf[4];
//	wiringPiI2CWrite(fd, CMD_HUM);
//	delay(100);
//	read(fd, buf, 3);
//	int hum = (buf[0] << 8 | buf[1]) & 0xFFFC;
//	double tSensorHumidity = -6 + (125 * hum / 65536.0);
//
//	return tSensorHumidity;
//}