#pragma once

#include "Msg.h"
#include "Msg_IncomingMQTT.h"

class Msg_IRCmd : public Msg
{
public:
	enum IRCmd
	{
		IR_UNKNOWN,
		IR_LED_ON,
		IR_LED_OFF,
		IR_LED_UP,
		IR_LED_DOWN
	};

	Msg_IRCmd(IRCmd cmd = IR_UNKNOWN);
	void fBuildFromMQTTMsg(Msg_IncomingMQTT* msg);	
	IRCmd fGetIRCmd();
private:
	IRCmd mCmd;
};

