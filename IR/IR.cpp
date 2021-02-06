#include "IR.h"

bool receivedCmd = 0;
ullong binMsg;

IRManager::IRManager() : Module()
{
	fSetModuleId(IR);
}

void IRManager::fOnStart()
{
	
}

void IRManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	logging::INFO("IRManager >> Received %s.", msg->fGetTypeAsString());
	switch (msg->fGetType())
	{
	case MsgType_IRCmd:
	{
		Msg_IRCmd* pMsg = static_cast<Msg_IRCmd*>(msg.get());
		if (pMsg)
		{
			switch (pMsg->fGetIRCmd())
			{
			case Msg_IRCmd::IR_LED_ON:
				fIRSend("00F7c03f");
				break;
			case Msg_IRCmd::IR_LED_OFF:
				fIRSend("00F740bf");
				break;
			case Msg_IRCmd::IR_LED_UP:
				fIRSend("00F700ff");
				break;
			case Msg_IRCmd::IR_LED_DOWN:
				fIRSend("00F7807f");
				break;
			default:
				break;
			}
		}
		break;
	}
	default:
		break;
	}
}


void fRemoteCallback(Remote* sender, ullong msg)
{
	binMsg = msg;
	receivedCmd = 1;
}

void IRManager::fRead()
{
	std::cout << "fRead()" << std::endl;
	int time = micros();
	duration = time - last;
	std::cout << duration << std::endl;
	remotes[1]->fReadPulse(duration);

	last = time;
}

void IRManager::fIRSend(const std::string& msg)
{
	//wiringPiSetupPhys();
	pinMode(OUT_PIN, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(84);
	pwmSetRange(6);

	remotes.push_back(new LED(&fRemoteCallback));
	
	std::vector<int> message = remotes[0]->fBuildMessage(msg);
	fSend(message);
	fSend(message);
	pwmWrite(OUT_PIN, 0);
}

void IRManager::fSend(const std::vector<int>& message)
{
	int delay, v;
	for (uint i = 0; i < message.size(); i++)
	{
		delay = message[i];
		v = ((i % 2) == 0) ? 3 : 0;
		pwmWrite(OUT_PIN, v);
		delayMicroseconds(delay);
	}
}