#include <iostream>
#include "ModuleBase.h"

using namespace std;


Module::Module() :
	mModuleId(Id::Not_Available), 
	mThread(nullptr), 
	mShouldExit(false), 
	mModuleName(mvModuleName[mModuleId].c_str())
{
}

Module::~Module()
{
	fStopModule();
}

bool Module::fStartModule()
{
	if (!mThread)
	{
		mThread = std::unique_ptr<std::thread>(new thread(&Module::fStart, this));
		logging::INFO("Module %s started. Thread Id: %d", mModuleName, std::this_thread::get_id());
	}
	else
	{
		logging::WARN("Module %s already started. Command ignored.", mModuleName);
	}
	return true;
}

void Module::fStopModule()
{
	if (!mThread)
		return;

	// Create a new ThreadMsg
	std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_EXIT_THREAD, 0));

	// Put exit thread message into the queue
	{
		lock_guard<mutex> lock(mMutex);
		mQueue.push(threadMsg);
		mCV.notify_one();
	}

    mThread->join();
    mThread = nullptr;
}

void Module::fPostMsg(std::shared_ptr<Msg> data)
{
	// Create a new ThreadMsg
    std::shared_ptr<ThreadMsg> threadMsg(new ThreadMsg(MSG_POST_DATA, data));

	// Add user data msg to queue and notify worker thread
	std::unique_lock<std::mutex> lk(mMutex);
	mQueue.push(threadMsg);
	mCV.notify_one();
}

void Module::fStart()
{
	fOnStart();
	while (1)
	{
		std::shared_ptr<ThreadMsg> msg;
		{
			// Wait for a message to be added to the queue
			std::unique_lock<std::mutex> lk(mMutex);
			while (mQueue.empty())
				mCV.wait(lk);

			if (mQueue.empty())
				continue;

			msg = mQueue.front();
			mQueue.pop();
		}

		switch (msg->id)
		{
			case MSG_POST_DATA:
			{
                auto userData = std::static_pointer_cast<Msg>(msg->msg);
				fProcessMessage(userData);
				break;
			}

			case MSG_EXIT_THREAD:
			{
				logging::INFO("Module %s stopped gracefully.", mModuleName);
                return;
			}

			default:
				;
		}
	}
}

void Module::fProcessMessage(std::shared_ptr<Msg> data)
{
	logging::ERROR("Default fProcessMessage ?!", mModuleName);
}


int Module::fGetModuleId()
{
	return mModuleId;
}

const char* Module::fGetModuleName()
{
	return mvModuleName[mModuleId].c_str();
}

void Module::fOnStart()
{
	logging::ERROR("Default onStart ?! %s", mModuleName);
}

std::thread::id Module::fGetThreadId()
{
	assert(mThread != nullptr);
	return mThread->get_id();
}

void Module::fSetModuleId(Id id)
{
	mModuleId = id;
	mModuleName = mvModuleName[id].c_str();
}