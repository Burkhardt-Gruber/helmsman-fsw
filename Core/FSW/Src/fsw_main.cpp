#include "fsw_main.h"

#include <memory>

#include "fsw_ipc.h"
#include "worker.h"
#include "example_wk.h"
#include "nucleo_watchdog_wk.h"
#include "cmsis_gcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "fsw_debug.h"
#include "task_nums.h"

// 3 second timeout
#define WD_TIMEOUT_MS 3000

/**
 * @brief Initialize global stuff
 */
static void GlobalInit();

/**
 * @brief Create the list of workers for the FSW
 */
static void CreateWorkers(void *arg);

extern "C" int FswMain(void *arg)
{
    CreateWorkers(arg);
    return 0;
}

void GlobalInit()
{
    __enable_irq();
    FswDebug::Init();
}

void CreateWorkers(void *arg)
{
    TaskHandle_t handle;

    // Stuff on the stack here gets nuked after the scheduler starts, so putting these on the heap
    // Should unique ptrs be used here?
    std::shared_ptr<FswIpc> ipc_ptr = std::make_shared<FswIpc>();
    ipc_ptr->Init();

    std::shared_ptr<Worker> ex_wk_0_ptr = std::make_shared<ExampleWk>(ipc_ptr);
    ex_wk_0_ptr->Init(arg);

    std::shared_ptr<Worker> watchdog_wk = std::make_shared<NucleoWatchdogWk>(ipc_ptr, WD_TIMEOUT_MS);
    watchdog_wk->Init(arg);

    GlobalInit();

    xTaskCreate(Worker::TaskFunction, "ExWk0", 2048, ex_wk_0_ptr.get(), 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)EXAMPLE_WK_0_NUM);

    xTaskCreate(Worker::TaskFunction, "Watchdog", 2048, watchdog_wk.get(), 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)WATCHDOG_NUM);

    vTaskStartScheduler();
}

