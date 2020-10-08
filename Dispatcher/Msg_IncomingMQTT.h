#pragma once

#include <string.h>

#include "Msg.h"

class Msg_IncomingMQTT : public Msg
{
public:
	Msg_IncomingMQTT(const char* subsId, const char* topic, const char* message);
	std::string fGetSubscriberId();
	std::string fGetTopic();
	std::string fGetMessage();
private:
	std::string mSubscriberId;
	std::string mTopic;
	std::string mMessage;
};

