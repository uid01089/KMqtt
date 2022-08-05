#include "CallbackEntry.h"

CallbackEntry::CallbackEntry(String topic, CallBackPtr fct)
{
    this->fct = fct;
    this->topic = topic;
}
CallbackEntry::~CallbackEntry()
{
}

String CallbackEntry::getTopic()
{
    return topic;
}
CallBackPtr CallbackEntry::getFct()
{
    return fct;
}
