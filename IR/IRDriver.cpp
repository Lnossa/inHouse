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
		wiringPiISR(IN_PIN, INT_EDGE_SETUP, &fIRRead);
		pinMode(OUT_PIN, PWM_OUTPUT);
		pwmSetMode(PWM_MODE_MS);
		pwmSetClock(84);
		pwmSetRange(6);

		mInitialized = true;
	}
}

void IRDriver::fEnableReceiver()
{
	if(system("/usr/bin/gpio edge 4 both") == 0)
	{
		logging::INFO("IRDriver >> Enabled receiver.");
	}
}

void IRDriver::fDisableReceiver()
{
	//This is currently the only way to disable an interrupt trigger
	//Pins in sys mode use BCM numbering 7 -> 4
	if(system("/usr/bin/gpio edge 4 none") == 0)
	{
		logging::INFO("IRDriver >> Disabled receiver.");
	}
}

void IRDriver::fIRSend(NECMsg* ipNecMsg)
{
	std::vector<int> message = fBuildMessage(ipNecMsg);

	fSend(message);
	fSend(message);

	pwmWrite(OUT_PIN, 0);

	logging::INFO("IRDriver >> Sent: Addr: 0x%02X, Data: 0x%02X", ipNecMsg->fGetAddr(), ipNecMsg->fGetCmd());
	delete ipNecMsg;
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
				mCallback(msg);
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


std::vector<int> IRDriver::fBuildMessage(NECMsg* ipMsg)
{

	std::vector<int> result;
	std::bitset<32> bitsetMsg = ipMsg->fEncode();

	

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
	fReadPulse(duration);

	last = time;
}


bool IRDriver::fIsInRange(const int& val, const int& range) {
	int err = range / 100 * ERR;

	return (val > range - err && val < range + err);
}


//======================================================================
//======================================================================

NECMsg::NECMsg(ullong iMsg) :
	mValid(0),
	mAddress(0),
	mCommand(0)
{
	fDecode(iMsg);
}

NECMsg::NECMsg(std::bitset<32> iMsg) :
	mValid(0),
	mAddress(0),
	mCommand(0)
{
	ullong lvMsg = iMsg.to_ullong();
	fDecode(lvMsg);
}

NECMsg::NECMsg(uint8_t iAddr, uint8_t iCmd) :
 mValid(1),
 mAddress(iAddr),
 mCommand(iCmd)
{
}

std::bitset<32> NECMsg::fEncode()
{
	ullong lvCodedMsg = 0;

	lvCodedMsg |= ~mCommand & 0xFF;
	lvCodedMsg |= (mCommand << 8);
	lvCodedMsg |= ((~mAddress & 0xFF) << 16);
	lvCodedMsg |= (mAddress << 24);

	return std::bitset<32>(lvCodedMsg);
}

bool NECMsg::fDecode(ullong iMsg)
{
	uint8_t lvAddr, lvAddrInv, lvCmd, lvCmdInv;

	lvAddr = (iMsg >> 24) & 0xFF;
	lvAddrInv = ~(iMsg >> 16) & 0xFF;
	lvCmd = (iMsg >> 8) & 0xFF;
	lvCmdInv = ~iMsg & 0xFF;
	
	if(lvAddr == lvAddrInv)
	{
		if(lvCmd == lvCmdInv)
		{
			mAddress = lvAddr;
			mCommand = lvCmd;
			mValid = true;
		}
	}
	return mValid;
}

uint8_t NECMsg::fGetAddr() const
{
	return mAddress;
}

uint8_t NECMsg::fGetCmd() const
{
	return mCommand;
}