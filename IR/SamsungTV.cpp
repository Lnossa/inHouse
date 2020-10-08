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
#include "SamsungTV.h"

#define ERR 15;

SamsungTV::SamsungTV(CallbackFunc cf) :
	Remote(cf)
{
	cState = RESET;
};


bool SamsungTV::fIsInRange(const int& val, const int& range) {
	int err = range / 100 * ERR;

	return (val > range - err && val < range + err);
}


void SamsungTV::fReadPulse(const int& duration)
{
	switch (cState)
	{
	case RESET:
		if (fIsInRange(duration, START))
		{
			pos = 0;
			msg.reset();
			cState = HEADER;
		}
		break;
	case HEADER:
		if (fIsInRange(duration, START))
			cState = DATA1;
		else
			cState = RESET;
		break;
	case DATA1:
		if (fIsInRange(duration, DATALOW))
		{
			if (pos == msg.size())
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
			msg[31 - pos++] = 0;
			cState = DATA1;
			break;
		}
		else if (fIsInRange(duration, DATAHIGH))
		{
			msg[31 - pos++] = 1;
			cState = DATA1;
			break;
		}
		else cState = RESET;
		break;
	default:
		break;
	}
}


std::vector<int> SamsungTV::fBuildMessage(const std::string& hexMsg)
{
	std::vector<int> result;
	result.clear();
	//Convert hex string to int
	ullong ullongMsg;
	std::stringstream ss;
	ss << std::hex << hexMsg;
	ss >> ullongMsg;

	//int to bitset
	std::bitset<32> bitsetMsg = std::bitset<32>(ullongMsg);
	std::cout << ullongMsg << std::endl;
	/*for (int i = 31; i >= 0 ; i--)
		std::cout << bitsetMsg[i];*/
	std::cout << std::endl;
	//Add header
	result.push_back(START);
	result.push_back(START);

	//Write message
	for (int i = 31; i >= 0; i--)
	{
		result.push_back(DATALOW);
		result.push_back(bitsetMsg[i] == 1 ? DATAHIGH : DATALOW);
	}

	//Add footer
	result.push_back(DATALOW);
	result.push_back(STOP);



	return result;
}

SamsungTV::~SamsungTV()
{
}


//switch ()
//{
//case DATALOW:
//	cmd = "DataLow";
//	break;
//case DATAHIGH:
//	cmd = "DataHigh";
//	break;
//case CTRLOW:
//	cmd = "CtrlLow";
//	break;
//case CTRMED:
//	cmd = "CtrlMed";
//	break;
//case CTRHIGH:
//	cmd = "CtrlHigh";
//	break;
//case STOP:
//	cmd = "StopLow";
//	break;
//case STOPHIGH:
//	cmd = "StopHigh";
//	break;
//default:
//	cmd = "MsgType_Undefined! " + std::to_string(timeDif);
//	break;




//int LED::fFindRange(const int& val) {
//	return
//		fIsInRange(val, DATALOW) ? DATALOW :
//		fIsInRange(val, DATAHIGH) ? DATAHIGH :
//		fIsInRange(val, CTRLOW) ? CTRLOW :
//		fIsInRange(val, CTRMED) ? CTRMED :
//		fIsInRange(val, CTRHIGH) ? CTRHIGH :
//		fIsInRange(val, STOP) ? STOP :
//		fIsInRange(val, STOPHIGH) ? STOPHIGH :
//		val > STOPHIGH ? STOPHIGH : -1;
//}