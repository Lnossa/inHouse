#include "Msg_IRCmd.h"
#include <jsoncpp/json/json.h>

uint8_t fHexToUInt(const char* vHex)
{
	int base = 16;
	if(strchr(vHex,'x'))
	{
		base = 0;
	}

	return strtol(vHex, NULL, base);
}

Msg_IRCmd::Msg_IRCmd(IRCmd cmd) : Msg(MsgType_IRCmd), mCmd(cmd)
{
}


void Msg_IRCmd::fBuildFromMQTTMsg(Msg_IncomingMQTT* msg)
{
	mCmd = IR_UNKNOWN;

	if(strcmp(msg->fGetTopic().c_str(), "irTpc") == 0)
	{
		Json::Reader lvJsonRdr;
		Json::Value lvJsonRoot;
		std::string lvMsgData = msg->fGetMessage();

		if(lvJsonRdr.parse(lvMsgData, lvJsonRoot))
		{
			mCmd = (IRCmd)lvJsonRoot["cmd"].asInt();
			if(mCmd == IR_SEND)
			{
				try
				{
					const char* lvAddrString = lvJsonRoot["addr"].asCString();
					const char* lvDataString = lvJsonRoot["data"].asCString();
					mAddr = fHexToUInt(lvAddrString);
					mData = fHexToUInt(lvDataString);
					logging::TRACE("Msg_IRCmd >> fBuildFromMQTTMsg() || Parsed Addr: %02X, Data: %02X", mAddr, mData);
				}
				catch(int e)
				{
					logging::ERROR("Msg_IRCmd >> fBuildFromMQTTMsg() || Caught exception (%d) while parsing Json", e);
				}
			}

		}
		else
		{
			logging::ERROR("Msg_IRCmd >> fBuildFromMQTTMsg() || Error parsing json!");
		}
	}
	// if (strcmp(msgData.c_str(), "ON") == 0)		mCmd = IR_LED_ON;
	// if (strcmp(msgData.c_str(), "OFF") == 0)	mCmd = IR_LED_OFF;
	// if (strcmp(msgData.c_str(), "UP") == 0)		mCmd = IR_LED_UP;
	// if (strcmp(msgData.c_str(), "DOWN") == 0)	mCmd = IR_LED_DOWN;
	// if (strcmp(msgData.c_str(), "RECV_ON") == 0)	mCmd = IR_RECV_ON;
	// if (strcmp(msgData.c_str(), "RECV_OFF") == 0)	mCmd = IR_RECV_OFF;
}

Msg_IRCmd::IRCmd Msg_IRCmd::fGetIRCmd()
{
	return mCmd;
}

uint8_t Msg_IRCmd::fGetAddr()
{
	return mAddr;
}

uint8_t Msg_IRCmd::fGetData()
{
	return mData;
}