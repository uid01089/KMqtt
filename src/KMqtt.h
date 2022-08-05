#ifndef KMQTT_H
#define KMQTT_H

#include <list>
#include <PubSubClient.h>

#include "Arduino.h"
#include "CallbackEntry.h"

class KMqtt
{
private:
    static std::list<CallbackEntry *> callbackList;
    static void mqttCallback(char *topic, byte *payload, unsigned int length);
    PubSubClient pubsubclient;
    static String payloadToString(byte *payload, unsigned int length);

public:
    KMqtt(const PubSubClient &pubsubclient);
    ~KMqtt();
    void setup(String domain, const uint16_t port, String id);
    void loop();
    void regCallBack(String topic, CallBackPtr fct);
    void publish(String topic, String payload);
};

#endif