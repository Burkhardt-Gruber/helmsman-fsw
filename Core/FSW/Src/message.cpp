#include "messasge.h"

Message::Message(taskid_t source, void *data) : source_(source) , data_(data) {}

void *Message::get_data()
{
    return data_;
}

taskid_t Message::get_source()
{
    return source_;
}