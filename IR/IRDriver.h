#pragma once
#include <bitset>
#include <vector>
#include <sstream>
#include <Logger/Logger.h>
#include "wiringPi.h"

#define IN_PIN 7
#define OUT_PIN 1

#define ERR 20

class NECMsg;
typedef unsigned long long ullong;
typedef void (*CallbackFunc)(NECMsg msg);

/*********************************
* IR driver class - Singleton    *
* Usage: IRDriver::getInstance() *
**********************************/
class IRDriver 
{

	/*
	NEC PROTOCOL:
		Data packet:
			- a 9ms leading pulse burst (16 times the pulse burst length used for a logical data bit)
			- a 4.5ms space
			- the 8-bit address for the receiving device
			- the 8-bit logical inverse of the address
			- the 8-bit command
			- the 8-bit logical inverse of the command
			- a final 562.5µs pulse burst to signify the end of message transmission.

		Data Format:
			- Logical '0' – a 562.5µs pulse burst followed by a 562.5µs space, with a total transmit time of 1.125ms
			- Logical '1' – a 562.5µs pulse burst followed by a 1.6875ms space, with a total transmit time of 2.25ms
	*/
	enum Range
	{
		DATALOW = 562,
		DATAHIGH = 1687,
		//CTRLOW = 2400,
		CTRMED = 4500,
		CTRHIGH = 9000,
		//STOPLOW = 39000,
		//STOPHIGH = 94000
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
	void fIRSend(NECMsg* ipNecMsg);

	//Set this to receive IR data from driver
	void fSetCallback(CallbackFunc cf);

	void fEnableReceiver();
	void fDisableReceiver();

private:

	//C'tor. Should be private.
	IRDriver();

	//Initialize
	void Init();

	//send
	void fSend(const std::vector<int>& message);
	std::vector<int> fBuildMessage(NECMsg* msg);
	

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

//Used for decoding and verifying data contained in NEC IR packets
class NECMsg
{

public:

	NECMsg() = delete;
	NECMsg(ullong iMsg);
	NECMsg(std::bitset<32> iMsg);
	NECMsg(uint8_t iAddr, uint8_t iCmd);

	bool fDecode(ullong iMsg);
	std::bitset<32> fEncode();
	

	uint8_t fGetAddr() const;
	uint8_t fGetCmd() const;

private:
	bool 	mValid;
	uint8_t mAddress;
	uint8_t mCommand;
};