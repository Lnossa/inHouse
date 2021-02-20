//////////////////////////  
//	LED Remote			//
//						//
//	CTRHIGH		CTRMED	//
//	DATALOW		DATA	//
//	DATALOW		DATA	//
//	.			.		//
//	.			.		//
//	DATALOW				//
//						//
//////////////////////////
#include<iostream>
#include "Remote.h"
#include "LED.h"

LED::LED(CallbackFunc cf) : 
	Remote(cf),
	pos(0)
{
	cState = RESET;
};


bool LED::fIsInRange(const int& val, const int& range) {
	int err = range / 100 * ERR;

	return (val > range - err && val < range + err);
}


void LED::fReadPulse(const int& duration)
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
			if (pos == msg.size()-1) 
			{
				callback(this, msg.to_ullong());
				cState = RESET;
			}
			cState = DATA2;
		}
		else
			cState = RESET;
		break;
	case DATA2:
		if (fIsInRange(duration, DATALOW))
		{
			msg[31-pos++] = 0;
			cState = DATA1;
			break;
		} 
		else if (fIsInRange(duration, DATAHIGH)) 
		{
			msg[31-pos++] = 1;
			cState = DATA1;
			break;
		}
		else cState = RESET;
		break;
	default:
		break;
	}
}


std::vector<int> LED::fBuildMessage(const std::string& hexMsg)
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
	result.push_back(STOPLOW);
	result.push_back(CTRHIGH);
	result.push_back(CTRLOW);
	result.push_back(DATALOW);
	result.push_back(STOPHIGH);
	result.push_back(CTRHIGH);
	result.push_back(CTRLOW);
	result.push_back(DATALOW);

	return result;
}

void LED::fAddPreamble(std::string msg)
{
	msg = "00F7" + msg;
}

LED::~LED()
{
}