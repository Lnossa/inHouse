#pragma once
#include <bitset>
#include "Remote.h"
#define ERR 20;


class LED : public Remote
{
	enum Range
	{
		DATALOW = 620,
		DATAHIGH = 1680,
		CTRLOW = 2400,
		CTRMED = 4300,
		CTRHIGH = 9100,
		STOPLOW = 39000,
		STOPHIGH = 94000
	};

	enum State 
	{
		RESET,
		HEADER,
		DATA1,
		DATA2,
		END
	};

	enum Key 
	{

	};

	
	State cState;
	unsigned int pos;
	std::bitset<32> msg;

	bool fIsInRange(const int& val, const int& range);

public:

	LED(CallbackFunc cf);
	~LED();
	void fAddPreamble(std::string msg);
	void fReadPulse(const int& duration);
	std::vector<int> fBuildMessage(const std::string& hexMsg);
};