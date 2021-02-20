#include "Dispatcher.h"

Dispatcher* gpDispatcher = 0;

Dispatcher::Dispatcher() 
{
	*mModuleList = { 0 };
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