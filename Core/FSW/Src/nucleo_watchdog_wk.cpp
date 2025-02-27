#include "nucleo_watchdog_wk.h"

#include "FreeRTOS.h"
#include "main.h"
#include "fsw_debug.h"

#define WD_ENABLE 0x0000CCCC
#define WD_REG_UNLOCK 0x0005555
#define WD_REFRESH 0x0000AAAA;

// Input clock 32kHz. 0x3 corresponds to /32, so 1kHz WD.
#define WD_PRESCALER 0x3

NucleoWatchdogWk::NucleoWatchdogWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t timeout) : WatchdogWk(ipc_ptr, timeout) {}

void NucleoWatchdogWk::Init(void *arg)
{
    (void)arg;

    // Stop watchdog when core is halted in debug mode
    DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP_Msk;

    // Enable the watchdog
    IWDG->KR = WD_ENABLE;

    // Enable register writing
    IWDG->KR = WD_REG_UNLOCK;

    // Write prescaler value - reset value is 0
    IWDG->PR = WD_PRESCALER;

    // Write reload reg - downcounting at 1kHz, so equals timeout_ms_
    IWDG->RLR = timeout_;

    // Wait for registers to be updated
    while(IWDG->SR);

    // Refresh counter
    IWDG->KR  = WD_REFRESH;
} 

void NucleoWatchdogWk::Tap()
{
    taskENTER_CRITICAL();
    IWDG->KR = WD_REFRESH;
    taskEXIT_CRITICAL();
}