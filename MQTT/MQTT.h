#pragma once

#include <stdio.h>
#include <string.h>
#include <mosquittopp.h>

#include "Dispatcher/Dispatcher.h"
#include "Dispatcher/Msg_IncomingMQTT.h"

class Mqtt : public mosqpp::mosquittopp
{
private:
	const char* host;
	const char* id;
	const char* topic;
	int                port;
	int                keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_subscribe(int mid, int qos_count, const int* granted_qos);
public:
	Mqtt(const char* id, const char* _topic, const char* host, int port);
	~Mqtt();
	bool send_message(const char* _message);
	bool fSubscribe();
	void on_message(const mosquitto_message* message);
};

