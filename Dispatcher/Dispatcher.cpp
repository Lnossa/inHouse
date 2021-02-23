#include "Dispatcher.h"

Dispatcher* gpDispatcher = 0;

Dispatcher::Dispatcher() 
{
	*mModuleList = { 0 };

	for (int i = 0; i < MAX_THREADS; i++)
		mModuleList[i] = 0;
}

void Dispatcher::fRegisterThread(Module* thread)
{
	if (thread->fGetModuleId() < MAX_THREADS)
	{
		mModuleList[thread->fGetModuleId()] = thread;
		logging::INFO("DISPATCHER >> fRegisterThread() || Registered %s with Dispatcher.", thread->fGetModuleName());
	}
	else
	{
		logging::ERROR("DISPATCHER >> fRegisterThread() || Thread limit [MAX_THREADS] exceeded.", thread->fGetModuleName());
	}
}

void Dispatcher::fUnregisterThread(Module* thread)
{
	if (thread != 0 && thread->fGetModuleId() < MAX_THREADS)
	{
		mModuleList[thread->fGetModuleId()] = 0;
		logging::INFO("DISPATCHER >> fUnRegisterThread() || Unregistered %s with Dispatcher.", thread->fGetModuleName());
	}
	else
	{
		logging::WARN("DISPATCHER >> fUnRegisterThread() || Thread not found.");
	}

}

void Dispatcher::fPostMessage(Module::Id moduleId, std::shared_ptr<Msg> msg)
{
	if (moduleId < MAX_THREADS && mModuleList[moduleId])
	{
		logging::DEBUG("DISPATCHER >> PostMessage() || %s to %s", msg->fGetTypeAsString(), mModuleList[moduleId]->fGetModuleName());
		mModuleList[moduleId]->fPostMsg(msg);
	}
	else
	{
		logging::ERROR("DISPATCHER >> PostMessage() || Module not found. %s not sent", msg->fGetTypeAsString());
	}
}

Module* Dispatcher::fGetModule(int id)
{
	return mModuleList[id];
}
