#include "watchdog_wk.h"

WatchdogWk::WatchdogWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t timeout) : Worker(ipc_ptr), timeout_(timeout) {}