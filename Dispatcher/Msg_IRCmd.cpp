#include "Msg_IRCmd.h"



Msg_IRCmd::Msg_IRCmd(IRCmd cmd) : Msg(MsgType_IRCmd), mCmd(cmd)
{
}


void Msg_IRCmd::fBuildFromMQTTMsg(Msg_IncomingMQTT* msg)
{
	std::string msgData = msg->fGetMessage();
	if (strcmp(msgData.c_str(), "ON") == 0)		mCmd = IR_LED_ON;
	if (strcmp(msgData.c_str(), "OFF") == 0)	mCmd = IR_LED_OFF;
	if (strcmp(msgData.c_str(), "UP") == 0)		mCmd = IR_LED_UP;
	if (strcmp(msgData.c_str(), "DOWN") == 0)	mCmd = IR_LED_DOWN;
}

Msg_IRCmd::IRCmd Msg_IRCmd::fGetIRCmd()
{
	return mCmd;
}