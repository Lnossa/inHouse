#include "Msg_IncomingMQTT.h"


Msg_IncomingMQTT::Msg_IncomingMQTT(const char* subsId, const char* topic, const char* message) :
	Msg(MsgType_IncomingMQTT),
	mSubscriberId(subsId),
	mTopic(topic),
	mMessage(message)
{
}

std::string Msg_IncomingMQTT::fGetSubscriberId()
{
	return mSubscriberId;
}
std::string Msg_IncomingMQTT::fGetTopic()
{
	return mTopic;
}
std::string Msg_IncomingMQTT::fGetMessage()
{
	return mMessage;
}