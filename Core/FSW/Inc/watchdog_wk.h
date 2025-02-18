#include "worker.h"

#include <cstdint>

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
     * @brief Tap the watchdog
     */
    virtual void Tap() = 0;
};