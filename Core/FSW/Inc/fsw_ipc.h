#pragma once

#include <memory>
#include <array>

#include "channel.h"
#include "task_nums.h"
#include "FreeRTOS.h"

/**
 * @brief Class which facilitates IPC between workers. IN RECV GET CALLING FUNCTION'S ID !!!
 */
class FswIpc
{
public:
    FswIpc();

    /**
     * @brief Initialize all channels
     */
    Status Init();

    /**
     * @brief Send a message to the supplied dest
     */
    Status Send(taskid_t dest_id, void *data, TickType_t block_time);

    /**
     * @brief Recieve a message on the caller's channel
     */
    Message Recv(TickType_t block_time);

    /**
     * @brief Get the number of messages waiting in the caller's channel
     */
    size_t NumMessagesWaiting();


private:
    // Array of channels
    std::array<std::unique_ptr<Channel>, WORKER_COUNT> channel_ptr_array;
};