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

	pOutgoingTempMqtt = new Mqtt("SensorTempMqtt", "tempStTpc", "localhost", 1883);
}
void MQTTManager::fProcessMessage(std::shared_ptr<Msg> msg)
{
	logging::INFO("MQTTManager >> Received %s.", msg->fGetTypeAsString());
	switch (msg->fGetType())
	{
	case MsgType_UpdateTemperatureInfo:
	{
		Msg_UpdateTemperatureInfo* pMsg = static_cast<Msg_UpdateTemperatureInfo*>(msg.get());
		logging::TRACE("MQTTManager >> Sensor: Temp: %.1f Hum: %.1f, Heat: %s", pMsg->fGetSensorTemperature(), pMsg->fGetSensorHumidity(), pMsg->fGetIsHeating() ? "ON" : "OFF");
		//std::string sTemp = std::to_string(pMsg->fGetSensorTemperature());
		pOutgoingTempMqtt->send_message(pMsg->fFormatAsJSON());
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
		if (strcmp(pMsg->fGetTopic().c_str(), "tempCmdTpc") == 0)
		{
			Msg_UpdateTemperatureInfo tempMsg;
			tempMsg.fBuildFromMQTTMsg(pMsg);
			auto spMsg = std::make_shared<Msg_UpdateTemperatureInfo>(tempMsg);
			gpDispatcher->fPostMessage(Temp, spMsg);
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