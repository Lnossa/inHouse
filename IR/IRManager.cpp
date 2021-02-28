#include "IRManager.h"

void fIRReceived(ullong msg);

IRManager::IRManager() : Module()
{
	fSetModuleId(IR);
	mpIRDriver = &IRDriver::getInstance();
}

void IRManager::fOnStart()
{
	mpIRDriver->fSetCallback(&fIRReceived);
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
				mpIRDriver->fIRSend("00F7c03f");
				break;
			case Msg_IRCmd::IR_LED_OFF:
				mpIRDriver->fIRSend("00F740bf");
				break;
			case Msg_IRCmd::IR_LED_UP:
				mpIRDriver->fIRSend("00F700ff");
				break;
			case Msg_IRCmd::IR_LED_DOWN:
				mpIRDriver->fIRSend("00F7807f");
				break;
			default:
				break;
			}
		}
		break;
	}
	default:
		logging::ERROR("Received unknown message: %s", msg->fGetTypeAsString());
		break;
	}
}

void IRManager::fOnStop()
{
	gpDispatcher->fUnregisterThread(this);
}


//Should be set as callback.
//Called by driver on incoming IR data.
void fIRReceived(ullong data)
{
	logging::TRACE("IR Received: %d", data);
}