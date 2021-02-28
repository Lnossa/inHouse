#include<iostream>
#include "IRDriver.h"

//Init static vars
int IRDriver::last = 0;
int IRDriver::duration = 0;
unsigned int IRDriver::pos = 0;
bool IRDriver::mInitialized = false;

std::bitset<32> IRDriver::msg = { 0 };
IRDriver::State IRDriver::cState = RESET;
CallbackFunc IRDriver::mCallback = NULL;


IRDriver::IRDriver()
{
	Init();
}


IRDriver& IRDriver::getInstance()
{
	static IRDriver instance;
	return instance;
}

void IRDriver::Init()
{
	if (!mInitialized)
	{
		pinMode(IN_PIN, INPUT);
		wiringPiISR(IN_PIN, INT_EDGE_BOTH, &fIRRead);
		pinMode(OUT_PIN, PWM_OUTPUT);
		pwmSetMode(PWM_MODE_MS);
		pwmSetClock(84);
		pwmSetRange(6);

		mInitialized = true;
	}
}

void IRDriver::fIRSend(const std::string& msg)
{
	std::vector<int> message = fBuildMessage(msg);

	fSend(message);
	fSend(message);

	pwmWrite(OUT_PIN, 0);
}

void IRDriver::fSetCallback(CallbackFunc cf)
{
	mCallback = cf;
}

void IRDriver::fReadPulse(const int& duration)
{
	switch (cState)
	{
	case RESET:
		if (fIsInRange(duration, CTRHIGH)) 
		{
			pos = 0;
			msg.reset();
			cState = HEADER;
		}
		break;
	case HEADER:
		if (fIsInRange(duration, CTRMED)) 
			cState = DATA1;
		else
			cState = RESET;
		break;
	case DATA1:
		if (fIsInRange(duration, DATALOW)) 
		{
			if (pos == msg.size()) 
			{
				NECMsg nMsg(msg);
				logging::TRACE("IRDriver >> NecMsg: Addr: %d(%02x), Cmd: %d(%02x)", nMsg.fGetAddr(), nMsg.fGetAddr(), nMsg.fGetCmd(), nMsg.fGetCmd());
				mCallback(msg.to_ullong());
				cState = RESET;
			}
			cState = DATA2;
		}
		else
		{
			cState = RESET;
		}
		break;
	case DATA2:
		if (fIsInRange(duration, DATALOW))
		{
			msg[31-pos] = 0;
			cState = DATA1;
			pos++;
			break;
		} 
		else if (fIsInRange(duration, DATAHIGH)) 
		{
			msg[31-pos] = 1;
			cState = DATA1;
			pos++;
			break;
		}
		else cState = RESET;
		break;
	default:
		break;
	}
}


std::vector<int> IRDriver::fBuildMessage(const std::string& hexMsg)
{
	std::vector<int> result;

	//Convert hex string to int
	ullong ullongMsg;
	std::stringstream ss;
	ss << std::hex << hexMsg;
	ss >> ullongMsg;

	//int to bitset
	std::bitset<33> bitsetMsg = std::bitset<33>(ullongMsg);

	//Add header
	result.push_back(CTRHIGH);
	result.push_back(CTRMED);

	//Write message
	for (int i = 31; i >= 0; i--)
	{
		result.push_back(DATALOW);
		result.push_back(bitsetMsg[i] == 1 ? DATAHIGH : DATALOW);
	}

	//Add footer
	result.push_back(DATALOW);
	//result.push_back(STOPLOW);
	result.push_back(CTRHIGH);
	//result.push_back(CTRLOW);
	result.push_back(DATALOW);
	//result.push_back(STOPHIGH);
	result.push_back(CTRHIGH);
	//result.push_back(CTRLOW);
	result.push_back(DATALOW);

	return result;
}

void IRDriver::fSend(const std::vector<int>& message)
{
	int delay, v;

	for (uint i = 0; i < message.size(); i++)
	{
		delay = message[i];
		v = ((i % 2) == 0) ? 3 : 0;
		pwmWrite(OUT_PIN, v);
		delayMicroseconds(delay);
	}
}


void IRDriver::fIRRead()
{
	
	int time = micros();
	duration = time - last;
	logging::TRACE("IRDriver >> fRead() || Duration: %d", duration);
	fReadPulse(duration);

	last = time;
}


bool IRDriver::fIsInRange(const int& val, const int& range) {
	int err = range / 100 * ERR;

	return (val > range - err && val < range + err);
}


//======================================================================
//======================================================================

NECMsg::NECMsg(std::bitset<32> msg) :
	mValid(0),
	mAddress(0),
	mCommand(0)
{
	ullong lvMsg = msg.to_ullong();
	uint8_t lvAddr, lvAddrInv, lvCmd, lvCmdInv;


	lvAddr = (lvMsg >> 24) & 0xFF;
	lvAddrInv = ~(lvMsg >> 16) & 0xFF;
	lvCmd = (lvMsg >> 8) & 0xFF;
	lvCmdInv = ~lvMsg & 0xFF;
	
	if(lvAddr == lvAddrInv)
	{
		if(lvCmd == lvCmdInv)
		{
			mAddress = lvAddr;
			mCommand = lvCmd;
			mValid = true;
		}
	}
}

uint8_t NECMsg::fGetAddr() const
{
	return mAddress;
}

uint8_t NECMsg::fGetCmd() const
{
	return mCommand;
}