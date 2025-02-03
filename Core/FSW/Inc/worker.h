#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

/**
 * @brief Worker class, which encapsulates the behavior for one asynronous worker. Has its own thread. Each process should define its own worker subclass. Workers should be implemented as fsms.
 */
class Worker
{
public:
    Worker();

    /**
     * @brief Task function, which will be used as the entry point for the thread for this worker. Calls FsmRunner and then spins.
     * @param task_permeters Necesary for FreeRTOS API stuff
     */
    void TaskFunction(void *task_parameters);    
    virtual ~Worker() = 0;

private:
    /**
     * @brief Setup logic that should be run before the RTOS thread is started. 
     */
    virtual void Setup() = 0;

    /**
     * @brief Runs the logic for this worker. Called by TaskFunction. Usually should not return.
     */
    virtual void Run() = 0;
};