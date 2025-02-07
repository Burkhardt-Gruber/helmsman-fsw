#include "fsw_main.h"

#include <memory>

#include "worker.h"
#include "example_wk.h"
#include "cmsis_gcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "fsw_debug.h"

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
    //Stuff on the stack here gets nuked after the scheduler starts, so putting these on the heap
    // Should unique ptrs be used here?
    std::unique_ptr<ExampleWk> ex_wk_0_ptr = std::make_unique<ExampleWk>();
    //ExampleWk *ex_wk_0_ptr = new ExampleWk;
    std::unique_ptr<ExampleWk> ex_wk_1_ptr = std::make_unique<ExampleWk>();
    //ExampleWk *ex_wk_1_ptr = new ExampleWk;

    ex_wk_0_ptr->Setup(arg);
    ex_wk_1_ptr->Setup(arg);

    GlobalInit();

    xTaskCreate(Worker::TaskFunction, "ExWk0", 2048, ex_wk_0_ptr.release(), 1, NULL);
    xTaskCreate(Worker::TaskFunction, "ExWk1", 2048, ex_wk_1_ptr.release(), 1, NULL);

    vTaskStartScheduler();
}

