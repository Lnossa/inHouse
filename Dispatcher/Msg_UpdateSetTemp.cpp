#include "Msg_UpdateSetTemp.h"


Msg_UpdateSetTemp::Msg_UpdateSetTemp()
	: Msg(MsgType::MsgType_UpdateSetTemp),
	mTemp(0)
{
}

int Msg_UpdateSetTemp::fGetTemperature()
{
	return mTemp;
}

void Msg_UpdateSetTemp::fBuildFromMQTTMsg(Msg_IncomingMQTT* pMsg)
{
	const char* msgData = pMsg->fGetMessage().c_str();
	mTemp = std::stoi(msgData);
}