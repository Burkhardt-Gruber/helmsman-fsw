#pragma once

#include <utility>
#include <cstddef>

#include "common.h"
#include "messasge.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

/**
 * @brief Channel for IPC between tasks. Encapsualtes FreeRTOS queue. Each task has a channel that it recieves messages on
 */
class Channel
{
public:
    Channel(taskid_t dest);

    /**
     * @brief Initialize channel
     * @return Channel status
     */
    Status Init();

    /**
     * @brief Sent a message on the channel. THREAD SAFE!!
     */
    Status Send(void *data, TickType_t block_time);

    /**
     * @brief Recieve a message on the channel. Should only be called by owner worker.
     * @return message.get_source = -1 if queue empty or block_time expires
     */
    Message Recv(TickType_t block_time);

    /**
     * @brief Get the number of messages in queue
     */
    size_t NumMessagesWaiting();

private:
    // Destination task id
    taskid_t dest_;

    // Queue handle
    QueueHandle_t queue_handle;

    // Sending semaphore
    SemaphoreHandle_t send_mutex;

    // Queue length 
    static constexpr size_t DEF_QUEUE_LEN = 10;
};