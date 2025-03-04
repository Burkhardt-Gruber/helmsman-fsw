#include "worker.h"

#include <cstdint>
#include <array>

#include "FreeRTOS.h"
#include "task_nums.h"

// Divisor by which the tick_timeout_ is divided to get tick_taks_timeout_
#define TICK_DIVISOR WORKER_COUNT

/**
 * @brief Worker for the watchdog. Checks the status of each task on the system, and given they're all good, taps the watchdog. Should be implemented for platform specific stuff
 */
class WatchdogWk : public Worker
{
public:
    WatchdogWk(std::shared_ptr<FswIpc> ipc_ptr_, uint32_t timeout);

protected:
    /**
     * @brief Watchdog timeout, in ms
     */
    uint32_t timeout_;

private:
    /**
     * @brief Watchdog timeout, in ticks
     */
    TickType_t tick_timeout_;

    /**
     * @brief Timeout for individual tasks, in ticks
     */
    TickType_t tick_tasks_timeout_;

    // Array of the tick count of the last tap from each worker/task
    std::array<TickType_t, WORKER_COUNT> times_since_taps_{};

    /**
     * @brief Initialize task timeouts
     */
    void TasksTimeoutInit();

    /**
     * @brief Get if the times since taps for each worker is within acceptable range
     */
    bool IsAllTimesValid(TickType_t current_time);

    /**
     * @brief Get if a time since last tap is within acceptable range
     */
    bool IsTimeValid(TickType_t last_tap_time, TickType_t current_time);

    void Run(void *arg) override;

    /**
     * @brief Tap the watchdog
     */
    virtual void Tap() = 0;
};