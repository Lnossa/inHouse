#pragma once
#include "Msg.h"
#include "Msg_IncomingMQTT.h"

class Msg_UpdateSetTemp : public Msg
{
public:
	Msg_UpdateSetTemp();

	int fGetTemperature();
	void fBuildFromMQTTMsg(Msg_IncomingMQTT* msg);
private:
	int mTemp;
};

