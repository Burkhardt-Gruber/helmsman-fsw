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
    struct TaskFunctionArg *tf_arg_array = new struct TaskFunctionArg[WORKER_COUNT];

    // Stuff on the stack here gets nuked after the scheduler starts, so putting these on the heap
    // Should unique ptrs be used here?
    std::shared_ptr<FswIpc> ipc_ptr = std::make_shared<FswIpc>();
    ipc_ptr->Init();

    std::shared_ptr<Worker> ex_wk_1_ptr = std::make_shared<ExampleWk>(ipc_ptr);
    ex_wk_1_ptr->Init(arg);

    std::shared_ptr<Worker> ex_wk_2_ptr = std::make_shared<ExampleWk>(ipc_ptr);
    ex_wk_2_ptr->Init(arg);

    std::shared_ptr<Worker> ex_wk_3_ptr = std::make_shared<ExampleWk>(ipc_ptr);
    ex_wk_3_ptr->Init(arg);

    std::shared_ptr<Worker> watchdog_wk_ptr = std::make_shared<NucleoWatchdogWk>(ipc_ptr, WD_TIMEOUT_MS);
    watchdog_wk_ptr->Init(arg);

    GlobalInit();

    tf_arg_array[EXAMPLE_WK_1_NUM].wk_ptr = ex_wk_1_ptr;
    tf_arg_array[EXAMPLE_WK_1_NUM].data = (void *)1000;
    xTaskCreate(Worker::TaskFunction, "ExWk1", 2048, &tf_arg_array[EXAMPLE_WK_1_NUM], 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)EXAMPLE_WK_1_NUM);

    tf_arg_array[EXAMPLE_WK_2_NUM].wk_ptr = ex_wk_2_ptr;
    tf_arg_array[EXAMPLE_WK_2_NUM].data = (void *)1000;
    xTaskCreate(Worker::TaskFunction, "ExWk2", 2048, &tf_arg_array[EXAMPLE_WK_2_NUM], 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)EXAMPLE_WK_2_NUM);

    tf_arg_array[EXAMPLE_WK_3_NUM].wk_ptr = ex_wk_3_ptr;
    tf_arg_array[EXAMPLE_WK_3_NUM].data = (void *)1000;
    xTaskCreate(Worker::TaskFunction, "ExWk3", 2048, &tf_arg_array[EXAMPLE_WK_3_NUM], 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)EXAMPLE_WK_3_NUM);

    tf_arg_array[WATCHDOG_NUM].wk_ptr = watchdog_wk_ptr;
    tf_arg_array[EXAMPLE_WK_1_NUM].data = (void *)1000;
    xTaskCreate(Worker::TaskFunction, "Watchdog", 2048, &tf_arg_array[WATCHDOG_NUM], 1, &handle);
    vTaskSetThreadLocalStoragePointer(handle, 0, (void *)WATCHDOG_NUM);

    vTaskStartScheduler();
}

