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
    Message msg(-1, NULL);

    while(1)
    {
        /*
        FswDebug::Log("Hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        */

        // Poll for a message (presumably from WD)
        while(ipc_ptr_->NumMessagesWaiting() == 0);
        msg = ipc_ptr_->Recv(0);

        if (msg.get_source() == WATCHDOG_NUM)
        {
            FswDebug::Log("Recieved message from WD.\n");
            ipc_ptr_->Send(WATCHDOG_NUM, NULL, 0);
            FswDebug::Log("Sent message back to WD.\n");
        }
        
        // Wait for a second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
