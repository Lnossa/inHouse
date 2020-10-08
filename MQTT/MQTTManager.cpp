#include "MQTTManager.h"

MQTTManager::MQTTManager() : Module()
{
	fSetModuleId(MQTT);
}

void MQTTManager::fOnStart()
{
	pLightsMqtt = new Mqtt("LightsMqtt", "lightsTpc", "localhost", 1883);
	pLightsMqtt->fSubscribe();

	pIncomingTempMqtt = new Mqtt("TempMqtt", "tempCmdTpc", "localhost", 1883);
	pIncomingTempMqtt->fSubscribe();

	pIncomingTempMqtt = new Mqtt("SensorTempMqtt", "tempStTpc", "localhost", 1883);
}
void MQTTManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	logging::INFO("MQTTManager >> Received %s.", msg->fGetTypeAsString());
	switch (msg->fGetType())
	{
	case MsgType_UpdateSensorTemp:
	{
		Msg_UpdateSensorTemp* pMsg = static_cast<Msg_UpdateSensorTemp*>(msg.get());
		logging::TRACE("MQTTManager >> Sensor: Temp: %.1f Hum: %.1f", pMsg->fGetTypeAsString(), pMsg->getTemperature(), pMsg->getHumidity());
		std::string sTemp = std::to_string(pMsg->getTemperature());
		pIncomingTempMqtt->send_message(sTemp.c_str());
		break;
	}
	case MsgType_IncomingMQTT:
	{
		Msg_IncomingMQTT* pMsg = static_cast<Msg_IncomingMQTT*>(msg.get());
		logging::TRACE("MQTTManager >> Incoming MQTT: Topic: %s Message: %s", pMsg->fGetTopic().c_str(), pMsg->fGetMessage().c_str());
		if (strcmp(pMsg->fGetTopic().c_str(), "lightsTpc") == 0)
		{
			Msg_IRCmd irMsg;
			irMsg.fBuildFromMQTTMsg(pMsg);
			auto spMsg = std::make_shared<Msg_IRCmd>(irMsg);
			gpDispatcher->fPostMessage(IR, spMsg);
		}
		break;
	}
	default:

		logging::WARN("MQTTManager >> Unexpected message: %s", msg->fGetTypeAsString());
		break;
	}

}


void MQTTManager::fProcessIncomingMQTT(Msg_IncomingMQTT* msg)
{
	//switch (msg->fGetTopic().c_str())
	//{
	//case "lightsTpc":
	//	break;
	//default:
	//	break;
	//}
}