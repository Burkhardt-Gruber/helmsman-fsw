#include "example_wk.h"

#include "fsw_debug.h"

void ExampleWk::Setup(void *arg)
{
    // No setup
}

void ExampleWk::Run(void *arg)
{
    while(1)
    {
        FswDebug::Log("Hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}