#include "Msg.h"


Msg::Msg(MsgType type) :
	mType(type)
{
}

MsgType& Msg::fGetType()
{
	return mType;
}

const char* Msg::fGetTypeAsString()
{
	return mvMsgNames[mType].c_str();
}