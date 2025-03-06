#include "watchdog_wk.h"

#include "fsw_debug.h"

WatchdogWk::WatchdogWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t timeout) : Worker(ipc_ptr), timeout_(timeout), tick_timeout_(pdMS_TO_TICKS(timeout)), tick_tasks_timeout_(tick_timeout_/TICK_DIVISOR) {}

void WatchdogWk::TasksTimeoutInit()
{
    TickType_t current_tick_count = xTaskGetTickCount();

    for (auto &tick_count : times_since_taps_)
    {
        tick_count = current_tick_count;
    }
}

bool WatchdogWk::IsAllTimesValid(TickType_t current_time)
{
    for (auto &last_tap_time : times_since_taps_)
    {
        if (!IsTimeValid(last_tap_time, current_time))
        {
            return false;
        }
    }

    return true;
}

bool WatchdogWk::IsTimeValid(TickType_t last_tap_time, TickType_t current_time)
{
    return (current_time - last_tap_time) < tick_tasks_timeout_;
}

void WatchdogWk::Run(void *arg)
{
    (void)arg;

    Message msg(-1, NULL);
    taskid_t msg_source;
    TickType_t current_tick_count;

    TasksTimeoutInit();

    while(1)
    {
        // Block waiting for a message
        msg = ipc_ptr_->Recv(portMAX_DELAY);
        msg_source = msg.get_source();

        // Check if recieved valid message - can't come from WD itself, so don't look at 0
        configASSERT(0 < msg_source && msg_source < WORKER_COUNT);

        current_tick_count = xTaskGetTickCount();

        // -1 since no watchdog
        times_since_taps_[msg_source-1] = current_tick_count;

        // If times valid, tap the watchdog
        if(IsAllTimesValid(current_tick_count))
        {
            Tap();
        }
    }
}
