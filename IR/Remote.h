#include<vector>
#include<string>
#include<sstream>
#include<bitset>
#pragma once

class Remote;
typedef unsigned long long ullong;
typedef void (*CallbackFunc)(Remote *sender, ullong msg);

class Remote
{
protected:
	CallbackFunc callback;
public:
	Remote(CallbackFunc cf) : callback(cf) {};
	virtual void fReadPulse(const int& duration) = 0;
	virtual std::vector<int> fBuildMessage(const std::string& hexMsg) = 0;
};

