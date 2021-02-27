#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <sys/file.h>
#include <signal.h>
#include <execinfo.h>

#include "IR/IRManager.h"
#include "MQTT/MQTTManager.h"
#include "LCD/LCDManager.h"
#include "Temp/TemperatureManager.h"
#include "Dispatcher/Dispatcher.h"
#include "Utils/Weather.h"
#include "Utils/Date.h"
#include "Logger/Logger.h"

void CreateLogFile();
void fSigSegvHandler(int sig);
void fSigIntHandler(int sig);
void fSigTermHandler(int sig);


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
		return -1;
	}

	CreateLogFile();
	
	int res = daemon(1, 1);
	if (res)
	{
		//failed
		logging::ERROR("Function daemon() failed. Return code: %d", res);
	}

		
	signal(SIGSEGV, fSigSegvHandler);
	signal(SIGINT, fSigIntHandler);
	signal(SIGTERM, fSigTermHandler);
		
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
		//Wait until 12 AM
		Date dt;
		tm* tomorrow = dt.fGetTime();
		tomorrow->tm_mday += 1;
		tomorrow->tm_hour = 0;
		tomorrow->tm_min = 0;
		tomorrow->tm_sec = 0;
		std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(mktime(tomorrow)));
		std::this_thread::sleep_for(std::chrono::hours(24));
		
		CreateLogFile();
	}
}


void fSigSegvHandler(int sig) {
	int fd;
	Date dt;
	void* array[10];
	size_t size;
	char filename[30];
	
	snprintf(filename, 30, "log/crash/%04d%02d%02d_%02d%02d.crash",
		dt.fGetYear(), dt.fGetMonth(), dt.fGetDay(), dt.fGetHour(), dt.fGetMinute());
	fd = open(filename, O_CREAT | O_WRONLY);

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);
	
	// print out all the frames to file
	logging::ERROR("Error: signal %d. See stack trace: %s", sig, filename);
	backtrace_symbols_fd(array, size, fd);
	
	close(fd);
	exit(1);
}

void fSigIntHandler(int sig)
{
	logging::INFO("SIGINT Received.");
	Module* lpModule;
	for (int i = 0; i < MAX_THREADS; i++)
	{
		if ((lpModule = gpDispatcher->fGetModule(i)) != 0)
			lpModule->fStopModule();
	}
}

void fSigTermHandler(int sig)
{
	logging::INFO("SIGTERM Received: %d", sig);
	Module* lpModule;
	for (int i = 0; i < MAX_THREADS; i++)
	{
		if ((lpModule = gpDispatcher->fGetModule(i)) != 0)
			lpModule->fStopModule();
	}
}

void CreateLogFile()
{
	Date dt;
	char logFileName[22];
	snprintf(logFileName, 22, "log/%04d%02d%02d_%02d%02d.log", dt.fGetYear(), dt.fGetMonth(), dt.fGetDay(), dt.fGetHour(), dt.fGetMinute());

	logging::configure({ {"type", "file"}, {"file_name", logFileName}, {"reopen_interval", "1"} });
	logging::INFO("New logfile created -> %s", logFileName);
}
