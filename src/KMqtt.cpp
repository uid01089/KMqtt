#include "KMqtt.h"

std::list<CallbackEntry *> KMqtt::callbackList;

KMqtt::KMqtt(const PubSubClient &pubsubclient)
{
    this->pubsubclient = pubsubclient;
}

KMqtt::~KMqtt()
{
}
void KMqtt::setup(String domain, const uint16_t port, String id)
{
    pubsubclient.setServer(domain.c_str(), port);
    while (!pubsubclient.connected())
    {
        pubsubclient.connect(id.c_str());
        delay(100);
    }

    pubsubclient.setCallback(KMqtt::mqttCallback);
}
void KMqtt::loop()
{
    pubsubclient.loop();
}

void KMqtt::regCallBack(String topic, std::function<void(String)> fct)
{
    CallbackEntry *scheduleEntry = new CallbackEntry(topic, fct);
    KMqtt::callbackList.push_back(scheduleEntry);
    pubsubclient.subscribe(topic.c_str());
}

void KMqtt::mqttCallback(char *topic, uint8_t *payload, unsigned int length)
{

    String topicAsString = String(topic);
    String payloadAsString = KMqtt::payloadToString(payload, length);

    for (CallbackEntry *entry : KMqtt::callbackList)
    {
        if (topicAsString == entry->getTopic())
        {
            // Call the function
            (entry->getFct())(payloadAsString);
        }
    }
}

void KMqtt::publish(String topic, String payload)
{
    pubsubclient.publish(topic.c_str(), payload.c_str());
}

String KMqtt::payloadToString(byte *payload, unsigned int length)
{
    char messageBuffer[length];             // somewhere to put the message
    memcpy(messageBuffer, payload, length); // copy in the payload
    messageBuffer[length] = '\0';
    return String(messageBuffer);
}
