#ifndef CALLBACK_ENTRY_h
#define CALLBACK_ENTRY_h

#include "Arduino.h"

typedef void (*CallBackPtr)(String payload);

class CallbackEntry
{

public:
    CallbackEntry(String topic, CallBackPtr fct);
    ~CallbackEntry();
    String getTopic();
    CallBackPtr getFct();

private:
    String topic;
    CallBackPtr fct;
};

#endif