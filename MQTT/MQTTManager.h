#pragma once

#include <mosquitto.h>
#include "MQTT.h"
#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_IncomingMQTT.h"
#include "Dispatcher/Msg_IRCmd.h"
#include "Dispatcher/Msg_UpdateTemperatureInfo.h"

class MQTTManager :	public Module
{
public:
	MQTTManager();

protected:
	void fOnStart() override;
	void fProcessMessage(std::shared_ptr<Msg> msg) override;

private:
	Mqtt* pLightsMqtt;
	Mqtt* pIncomingTempMqtt;
	Mqtt* pOutgoingTempMqtt;

	void fProcessIncomingMQTT(Msg_IncomingMQTT* msg);
};

