#include "fsw_main.h"


#include "worker.h"
#include "uart_debug_wk.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

/**
 * @brief Initialize global stuff
 */
static void global_init();

/**
 * @brief Create the list of workers for the FSW
 */
static void create_workers(void *arg);

extern "C" int fsw_main(void *arg)
{
    create_workers(arg);
    return 0;
}

void global_init()
{
    __enable_irq();
}

void create_workers(void *arg)
{
    UartDebugWk uart_debug_wk;

    uart_debug_wk.Setup(arg);
    //global_init();

    xTaskCreate(Worker::TaskFunction, "Uart Debug", 1000, &uart_debug_wk, 1, NULL);

    vTaskStartScheduler();
}

