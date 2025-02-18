#pragma once

#include <typeindex>
#include <cstddef>

#include "common.h"

/**
 * @brief Class which represents a message for IPC. Used by Channel class.
 */
class Message
{
public:
    Message(taskid_t source, void *data);
    
    void *get_data();

    taskid_t get_source();
    
private:
    // Message source task
    taskid_t source_;

    // Data pointer
    void *data_;
};