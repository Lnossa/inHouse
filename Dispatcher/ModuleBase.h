#ifndef _THREAD_STD_H
#define _THREAD_STD_H

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <string>
#include <assert.h>
#include <condition_variable>

#include "Msg.h"
#include "Logger/Logger.h"

#define MSG_EXIT_THREAD			1
#define MSG_POST_DATA			2

struct ThreadMsg
{
	ThreadMsg(int i, std::shared_ptr<void> m) { id = i; msg = m; }
	int id;
	std::shared_ptr<void> msg;
};


class Module
{

public:

	// Keep in sync with mvModuleName !!
	// Also affects dispatcher load order !!
	enum Id		
	{			
		Not_Available = 0,
		MQTT = 1,
		LCD = 2,
		IR = 3,	
		RF = 4,	
		Temp = 5
	};			

private:
	
	Id mModuleId;
	
	std::mutex mMutex;
	std::condition_variable mCV;
	std::unique_ptr<std::thread> mThread;
	std::queue<std::shared_ptr<ThreadMsg>> mQueue;
	std::atomic<bool> mShouldExit;

	// Keep in sync with enum Id
	std::vector<std::string> mvModuleName =	
	{
		"Not_Available",
		"MQTT",								
		"LCD",								
		"IR",								
		"RF",								
		"Temp"								
	};										

	const char* mModuleName;

	//Deleted methods
	Module(const Module&) = delete;
	Module& operator=(const Module&) = delete;

	/// Entry point for the worker thread
	void fStart();

protected:
	//Methods that should be overridden
	virtual void fOnStart();
	virtual void fProcessMessage(std::shared_ptr<Msg> msg);

	//Thread related methods
	std::thread::id fGetThreadId();

	void fSetModuleId(Id id);

public:
    //C'tor & d'tor
    Module();
    ~Module();

    bool fStartModule();
    void fStopModule();

	int fGetModuleId();
	const char* fGetModuleName();

    //Add message to queue
    void fPostMsg(std::shared_ptr<Msg> msg);
};

#endif 

