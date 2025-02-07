#include "worker.h"

/**
 * @brief Worker for the watchdog. Checks the status of each task on the system, and given they're all good, taps the watchdog.
 */
class WatchdogWk : public Worker
{
public:
    void Setup(void *arg) override;

private:
    void Run(void *arg) override;
};