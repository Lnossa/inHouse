#pragma once
#include<iostream>

#include "IRDriver.h"
#include "Dispatcher/Msg_IRCmd.h"
#include "Dispatcher/Dispatcher.h"


class IRManager : public Module
{

private:
	IRDriver* mpIRDriver;

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;
	void fOnStop() override;
public:
	IRManager();
};

