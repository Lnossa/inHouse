#include "MQTT.h"

Mqtt::Mqtt(const char* _id, const char* _topic, const char* _host, int _port) : mosquittopp(_id)
{
	mosqpp::lib_init();        // Mandatory initialization for mosquitto library
	this->keepalive = 60;    // Basic configuration setup for Mqtt class
	this->id = _id;
	this->port = _port;
	this->host = _host;
	this->topic = _topic;
	mosquittopp::username_pw_set("openhabian", "passwd123");
	connect_async(host,     // non blocking connection to broker request
		port,
		keepalive); 
	loop_start();            // Start thread managing connection / publish / subscribe
};


Mqtt::~Mqtt() {
	loop_stop();            // Kill the thread
	mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

bool Mqtt::send_message(const  char * _message)
 {
 int ret = publish(NULL,this->topic,strlen(_message),_message,1,false);
 logging::TRACE("MQTT >> %s || Sent %s on topic %s.", id, _message, this->topic);
 return ( ret == MOSQ_ERR_SUCCESS );
 }

bool Mqtt::send_message(std::shared_ptr<char> _message)
{
	int ret = publish(NULL, this->topic, strlen(_message.get()), _message.get(), 1, false);
	logging::TRACE("MQTT >> %s || Sent %s on topic %s.", id, _message.get(), this->topic);
	return (ret == MOSQ_ERR_SUCCESS);
}

bool Mqtt::fSubscribe()
{
	int set = subscribe(NULL, this->topic, 2);
	return set;
}

void Mqtt::on_disconnect(int rc) {
	logging::TRACE("MQTT >> %s || Disconnected (%d).", id, rc);

}

void Mqtt::on_message(const mosquitto_message* message)
{
	char* pMqttMsg = reinterpret_cast<char*>(message->payload);
	logging::TRACE("MQTT >> %s || Received message. Topic: %s. Data: %s", id, message->topic, pMqttMsg);
	Msg_IncomingMQTT pMsg(id, message->topic, pMqttMsg);
	auto psMsg = std::make_shared<Msg_IncomingMQTT>(pMsg);
	gpDispatcher->fPostMessage(Module::Id::MQTT, psMsg);
}

void Mqtt::on_connect(int rc)
{
	if (rc == 0) 
	{
		logging::TRACE("MQTT >> %s || Connected with server.", this->id);
	}
	else 
	{
		logging::TRACE("MQTT >> %s || Connection failed(%d).", this->id, rc);
	}
}

void Mqtt::on_subscribe(int mid, int qos_count, const int* granted_qos)
{
	logging::TRACE("MQTT >> %s || Subscription succeeded. Topic %s.", this->id, this->topic);
}