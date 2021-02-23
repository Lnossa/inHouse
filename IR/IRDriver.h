#pragma once
#include <bitset>
#include <vector>
#include <sstream>
#include "wiringPi.h"

#define IN_PIN 7
#define OUT_PIN 1

#define ERR 20

typedef unsigned long long ullong;
typedef void (*CallbackFunc)(ullong msg);

/*********************************
* IR driver class - Singleton    *
* Usage: IRDriver::getInstance() *
**********************************/
class IRDriver 
{
	enum Range
	{
		DATALOW = 620,
		DATAHIGH = 1680,
		CTRLOW = 2400,
		CTRMED = 4300,
		CTRHIGH = 9100,
		STOPLOW = 39000,
		STOPHIGH = 94000
	};

	enum State 
	{
		RESET,
		HEADER,
		DATA1,
		DATA2,
		END
	};

public:
	//Get driver instance
	static IRDriver& getInstance();

	//Send IR message
	void fIRSend(const std::string& msg);

	//Set this to receive IR data from driver
	void fSetCallback(CallbackFunc cf);

private:

	//C'tor. Should be private.
	IRDriver();

	//Initialize
	void Init();

	//send
	void fSend(const std::vector<int>& message);
	void fAddPreamble(std::string msg);
	std::vector<int> fBuildMessage(const std::string& hexMsg);
	

	//receive (static)
	static void fIRRead();
	static void fReadPulse(const int& duration);

	//Helper. Used for allowing slight errors in timing
	//See #define ERR 20 in IRDriver.h
	static bool fIsInRange(const int& val, const int& range);
	

private:

	static int last;
	static int duration;
	static unsigned int pos;
	static bool mInitialized;

	static State cState;
	static std::bitset<32> msg;
	static CallbackFunc mCallback;


public:
	//Disabled functions
	//Copy and assignment constructors illegal
	IRDriver(IRDriver const&) = delete;
	void operator=(IRDriver const&) = delete;
};
