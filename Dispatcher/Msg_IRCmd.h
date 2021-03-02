#pragma once

#include "Msg.h"
#include "Msg_IncomingMQTT.h"
#include <Logger/Logger.h>

class Msg_IRCmd : public Msg
{
public:
	enum IRCmd
	{
		IR_UNKNOWN,
		IR_SEND,
		IR_RECV_ON,
		IR_RECV_OFF
	};

	Msg_IRCmd(IRCmd cmd = IR_UNKNOWN);
	void fBuildFromMQTTMsg(Msg_IncomingMQTT* msg);	
	IRCmd fGetIRCmd();
	uint8_t fGetAddr();
	uint8_t fGetData();
private:
	IRCmd mCmd;
	uint8_t mAddr;
	uint8_t mData;
};

