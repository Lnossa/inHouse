#include "Msg_IRCmd.h"



Msg_IRCmd::Msg_IRCmd(IRCmd cmd) : Msg(MsgType_IRCmd), mCmd(cmd)
{
}


void Msg_IRCmd::fBuildFromMQTTMsg(Msg_IncomingMQTT* msg)
{
	const char* msgData = msg->fGetMessage().c_str();
	if (strcmp(msgData, "ON") == 0)		mCmd = IR_LED_ON;
	if (strcmp(msgData, "OFF") == 0)	mCmd = IR_LED_OFF;
	if (strcmp(msgData, "UP") == 0)		mCmd = IR_LED_UP;
	if (strcmp(msgData, "DOWN") == 0)	mCmd = IR_LED_DOWN;
}

Msg_IRCmd::IRCmd Msg_IRCmd::fGetIRCmd()
{
	return mCmd;
}