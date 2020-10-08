//#include<iostream>
//#include<math.h>
//#include "wiringPi.h"
//#include "Remote.h"
//#include "LED.h"
//#include "SamsungTV.h"
//
//#define IN_PIN 7
//#define OUT_PIN 12
//
//
//int last;
//int duration;
//bool receivedCmd = 0;
//ullong binMsg;
//
//std::vector<Remote*> remotes;
//
//void fRemoteCallback(Remote *sender, ullong msg) 
//{
//	binMsg = msg;
//	receivedCmd = 1;
//}
//
//void fRead()
//{
//	std::cout << "fRead()" << std::endl;
//	int time = micros();
//	duration = time - last;
//	std::cout << duration << std::endl;
//	remotes[1]->fReadPulse(duration);
//	
//	last = time;
//}
//
//void fSend(const std::vector<int>& message)
//{
//	int delay, v;
//	for (uint i = 0; i < message.size(); i++)
//	{
//		delay = message[i];
//		v = ((i % 2) == 0) ? 3 : 0;
//		pwmWrite(OUT_PIN, v);
//		delayMicroseconds(delay);
//	}
//	std::cout << "Message sent" << std::endl;
//}
//
//
//
//int main()
//{
//	//std::string msg = "807F";
//	//LED* led1 = new LED(&fRemoteCallback);
//	//led1->fAddPreamble(msg);
//	//std::cout << msg;
//
//
//	wiringPiSetupPhys();
//	pinMode(IN_PIN, INPUT);
//	wiringPiISR(IN_PIN, INT_EDGE_BOTH, &fRead);
//	pinMode(OUT_PIN, PWM_OUTPUT);
//	pwmSetMode(PWM_MODE_MS);
//	pwmSetClock(84);
//	pwmSetRange(6);
//
//	remotes.push_back(new LED(&fRemoteCallback));
//	remotes.push_back(new SamsungTV(&fRemoteCallback));
//
//	//std::vector<int> message = remotes[1]->fBuildMessage("e0e0e01f");
//	std::vector<int> message = remotes[0]->fBuildMessage("00F7807F");
//
//	//while (1)
//	//{
//	//	fSend(message);
//	//}
//
//	std::cout << "Start" << std::endl;
//
//	while (1) {
//		if (receivedCmd == 1) {
//			std::cout << std::hex << binMsg << std::endl;
//			receivedCmd = 0;
//		}
//		delay(50);
//	}
//
//
//	return 0;
//}

int main()
{
	return 0;
}