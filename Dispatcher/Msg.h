#pragma once
#include <string>
#include <vector>
#include <memory>

enum MsgType
{
	MsgType_Undefined,
	MsgType_UpdateSensorTemp,
	MsgType_UpdateWeather,
	MsgType_IncomingMQTT,
	MsgType_IRCmd
};

class Msg
{
public:
	Msg(MsgType = MsgType_Undefined);
	virtual MsgType& fGetType();
	const char* fGetTypeAsString();

private:
	MsgType mType;
	std::vector<std::string> mvMsgNames =
	{
		"UNDEFINED",
		"Msg_UpdateSensorTemp",
		"Msg_UpdateWeather",
		"Msg_IncomingMQTT",
		"Msg_IRCmd"
	};

};

