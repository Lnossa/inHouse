#include "MQTTManager.h"

MQTTManager::MQTTManager() : Module()
{
	pLightsMqtt = new Mqtt("LightsMqtt", "lightsTpc", "localhost", 1883);
	pIncomingTempMqtt = new Mqtt("TempMqtt", "tempCmdTpc", "localhost", 1883);
	pOutgoingTempMqtt = new Mqtt("SensorTempMqtt", "tempStTpc", "localhost", 1883);

	fSetModuleId(MQTT);
}

void MQTTManager::fOnStart()
{
	pLightsMqtt->fSubscribe();
	pIncomingTempMqtt->fSubscribe();

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

void MQTTManager::fOnStop()
{
	pLightsMqtt->loop_stop(true);
	pIncomingTempMqtt->loop_stop(true);
	pOutgoingTempMqtt->loop_stop(true);
	gpDispatcher->fUnregisterThread(this);
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