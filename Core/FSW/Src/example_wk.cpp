#include "example_wk.h"

#include "fsw_debug.h"
#include "FreeRTOS.h"
#include "fsw_util.h"

ExampleWk::ExampleWk(std::shared_ptr<FswIpc> ipc_ptr) : Worker(ipc_ptr) {}

void ExampleWk::Init(void *arg)
{
    (void)(arg);
}

void ExampleWk::Run(void *arg)
{
    Message msg(-1, NULL);
    uint32_t wd_tap_delay_ms = (uint32_t)arg;

    while(1)
    {
        // Tap WD
        ipc_ptr_->Send(WATCHDOG_NUM, NULL, portMAX_DELAY);
        FswDebug::Log("Task %lu sending to WD task.", FswUtil::GetId());

        vTaskDelay(pdMS_TO_TICKS(wd_tap_delay_ms));

        /*
        FswDebug::Log("Hello!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

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
        */
    }
}
