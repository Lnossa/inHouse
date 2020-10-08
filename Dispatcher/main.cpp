#include <iostream>
#include <chrono>

//#include "WorkerThread.h"
#include "Dispatcher.h"


//// Worker thread instances
//WorkerThread mqttThread(WorkerThread::ModuleId::MQTT);
//WorkerThread lcdThread(WorkerThread::ModuleId::LCD);
//WorkerThread irThread(WorkerThread::ModuleId::IR);
//
//class test : public WorkerThread
//{
//	using WorkerThread::WorkerThread;
//	void ProcessMessage(std::shared_ptr<Msg> data) override
//	{
//		std::cout << "Test Thread processed data: " << data->msg << " " << data->year << std::endl;
//		std::shared_ptr<Msg> userData1(new Msg());
//		userData1->msg = "Inter-Thread";
//		userData1->year = 2021;
//		Dispatcher::postMessage(WorkerThread::ModuleId::MQTT, userData1);
//	}
//};
//
//test rfThread(WorkerThread::ModuleId::RF);

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(void)
{	
	//// Create worker threads
	//mqttThread.CreateThread();
	//lcdThread.CreateThread();
	//irThread.CreateThread();
	//rfThread.CreateThread();
	//Dispatcher rDisp = Dispatcher::getInstance();
	//rDisp.addThread(&mqttThread);
	//rDisp.addThread(&lcdThread);
	//rDisp.addThread(&irThread);
	//rDisp.addThread(&rfThread);

	//// Create message to send to worker thread 1
	//std::shared_ptr<Msg> userData1(new Msg());
	//userData1->msg = "Hello world";
	//userData1->year = 2017;

	//// Post the message to worker thread 1

	//// Create message to send to worker thread 2
	//std::shared_ptr<Msg> userData2(new Msg());
	//userData2->msg = "Goodbye world";
	//userData2->year = 2017;

	//// Post the message to worker thread 2
	//
	//Dispatcher::postMessage(WorkerThread::ModuleId::LCD, userData1);
	//Dispatcher::postMessage(WorkerThread::ModuleId::IR, userData2);
	////workerThread1.PostMsg(userData1);
	////workerThread2.PostMsg(userData2);

	//// Give time for messages processing on worker threads
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::shared_ptr<Msg> userData3(new Msg());
	//userData3->msg = "test world";
	//userData3->year = 2020;
	////testThread.PostMsg(userData3);
	//Dispatcher::postMessage(WorkerThread::ModuleId::RF, userData3);

	//std::this_thread::sleep_for(std::chrono::seconds(5));

	//lcdThread.ExitThread();
	//irThread.ExitThread();

	return 0;
}

