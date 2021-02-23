#pragma once

#include <iostream>
#include <vector> 
#include "ModuleBase.h"

#define MAX_THREADS 10

class Dispatcher
{
private:
	Module* mModuleList[MAX_THREADS];
public:
	Dispatcher();
	void fRegisterThread(Module* thread);
	void fUnregisterThread(Module* thread);
	void fPostMessage(Module::Id moduleId, std::shared_ptr<Msg> msg);
	Module* fGetModule(int id);
};

//Global pointer
extern Dispatcher* gpDispatcher;


