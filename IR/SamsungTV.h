#pragma once
#include "Remote.h"
class SamsungTV : public Remote
{
	enum Range
	{
		START = 4200,
		DATALOW = 500,
		DATAHIGH = 1600,
		STOP = 46000
	};

	typedef enum
	{
		RESET,
		HEADER,
		DATA1,
		DATA2,
		END
	} State;


	State cState;
	int lastTime;
	unsigned int pos;
	std::bitset<32> msg;

	bool fIsInRange(const int& val, const int& range);

public:

	SamsungTV(CallbackFunc cf);
	~SamsungTV();
	void fReadPulse(const int& duration);
	std::vector<int> fBuildMessage(const std::string& hexMsg);
};

