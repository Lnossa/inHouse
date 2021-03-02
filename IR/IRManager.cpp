#include "IRManager.h"

void fIRReceived(NECMsg msg);

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
			case Msg_IRCmd::IR_SEND:
			{
				NECMsg* lpMsg = new NECMsg(pMsg->fGetAddr(), pMsg->fGetData());
				mpIRDriver->fIRSend(lpMsg);
				break;
			}
			case Msg_IRCmd::IR_RECV_ON:
			{
				mpIRDriver->fEnableReceiver();
				break;
			}
			case Msg_IRCmd::IR_RECV_OFF:
			{
				mpIRDriver->fDisableReceiver();
				break;
			}
			case Msg_IRCmd::IR_UNKNOWN:
			default:
				logging::ERROR("IRManager >> Received unkown IRCmd");
				break;
			}
		}
		break;
	}
	default:
		logging::ERROR("IRManager >> Received unknown message: %s", msg->fGetTypeAsString());
		break;
	}
}

void IRManager::fOnStop()
{
	gpDispatcher->fUnregisterThread(this);
}


//Should be set as callback.
//Called by driver on incoming IR data.
void fIRReceived(NECMsg msg)
{
	logging::TRACE("IR Received -> Addr: %02X, Cmd: %02X", msg.fGetAddr(), msg.fGetCmd());
}