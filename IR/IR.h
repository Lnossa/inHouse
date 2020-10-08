#pragma once
#include<iostream>

#include "LED.h"
#include "Remote.h"
#include "wiringPi.h"
#include "Dispatcher/Msg_IRCmd.h"
#include "Dispatcher/Dispatcher.h"

#define IN_PIN 7
#define OUT_PIN 12

class IRManager : public Module
{

private:
	int last;
	int duration;
	bool receivedCmd = 0;
	ullong binMsg;
	std::vector<Remote*> remotes;
	void fRead();
	void fSend(const std::vector<int>& message);
	void fIRSend(const std::string& msg);

protected:
	//void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;

public:
	IRManager();
};

