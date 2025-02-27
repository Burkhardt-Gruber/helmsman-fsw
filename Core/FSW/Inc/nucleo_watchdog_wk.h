#include "watchdog_wk.h"

/**
 * @brief STM32F746ZG (the one on the nucleo) implementation of the watchdog
 */
class NucleoWatchdogWk : public WatchdogWk
{
public:
    NucleoWatchdogWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t timeout);

    /**
     * @brief Initialize the watchdog peripheral
     */
    void Init(void *arg) override;

private:
    void Tap() override;
};