#include "example_wk.h"

#include "fsw_debug.h"

ExampleWk::ExampleWk(std::shared_ptr<FswIpc> ipc_ptr) : Worker(ipc_ptr) {}

void ExampleWk::Init(void *arg)
{
    (void)(arg);
}

void ExampleWk::Run(void *arg)
{
    (void)(arg);
    while(1)
    {
        FswDebug::Log("Hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
