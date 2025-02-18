#pragma once

#include <memory>

#include "common.h"
#include "channel.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "fsw_ipc.h"

/**
 * @brief Worker class, which encapsulates the behavior for one asynronous worker. Has its own thread. Each process should define its own worker subclass. Workers should be implemented as fsms.
 * ALL FUNCTIONS EXEPT FOR SendMsg and TaskFunction SHOULD BE CALLED BY THIS WORKER'S THREAD
 */
class Worker
{
public:
    Worker(std::shared_ptr<FswIpc> ipc_ptr);

    /**
     * @brief Task function, which will be used as the entry point for the thread for this worker. Calls Run.
     * @param wk Pointer to the Worker class to be run
     */
    static void TaskFunction(void *arg);

    /**
     * @brief Initialize stuff
     */
    virtual void Init(void *arg) = 0;

    virtual ~Worker();

private:
    std::shared_ptr<FswIpc> ipc_ptr_;

    /**
     * @brief Runs the logic for this worker. Called by TaskFunction. Usually should not return.
     */
    virtual void Run(void *arg) = 0;
};