#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <sys/file.h>

#include "IR/IR.h"
#include "MQTT/MQTTManager.h"
#include "LCD/LCDManager.h"
#include "Temp/TemperatureManager.h"
#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_UpdateSensorTemp.h"
#include "Utils/Weather.h"
#include "Utils/Date.h"
#include "Logger/Logger.h"
#include "IR/IR.h"

int main()
{
	FILE* fLock;
	if ((fLock = fopen("file.lock", "r")) == NULL)
	{
		logging::ERROR("file.lock not found");
		return -1;
	}
	if (flock(fileno(fLock), LOCK_EX | LOCK_NB) < 0)
	{
		logging::ERROR("Process is already running");
		return -1;
	}

	if (wiringPiSetup() == -1) {
		logging::ERROR("wiringPiSetup() error!");
		return 0;
	}
	
	daemon(1, 1);
	
	logging::configure({ {"type", "file"}, {"file_name", "test.log"}, {"reopen_interval", "1"} });
	logging::INFO("Program start. Main Thread Id: %d", std::this_thread::get_id());
	gpDispatcher = new Dispatcher;

	MQTTManager mqttModule;
	if (mqttModule.fStartModule())
		gpDispatcher->fRegisterThread(&mqttModule);

	IRManager irModule;
	if (irModule.fStartModule())
		gpDispatcher->fRegisterThread(&irModule);

	LCDManager lcdModule;
	if(lcdModule.fStartModule())
		gpDispatcher->fRegisterThread(&lcdModule);
	
	TemperatureManager tempModule;
	if(tempModule.fStartModule())
		gpDispatcher->fRegisterThread(&tempModule);
	


	while (true)
	{
		std::this_thread::sleep_for(std::chrono::hours(24));
	}
}


