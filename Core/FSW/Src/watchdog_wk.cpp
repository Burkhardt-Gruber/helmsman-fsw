#include "watchdog_wk.h"

#include "fsw_debug.h"

WatchdogWk::WatchdogWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t timeout) : Worker(ipc_ptr), timeout_(timeout) {}

void WatchdogWk::Run(void *arg)
{
    (void)arg;
    Message msg(-1, NULL);
    size_t wd_tap_count = 0;

    while(1)
    {
        /*
        for(int i = 0; i < 3; i++)
        {
            FswDebug::Log("Tapping WD #%i\n", i);
            Tap();
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        FswDebug::Log("Letting WD restart!\n");
        vTaskSuspend(NULL);
        */
        
        // Send a message to EXAMPLE_WK_0
        ipc_ptr_->Send(EXAMPLE_WK_0_NUM, NULL);
        FswDebug::Log("Sending message to wk_0.\n");

        // Poll reciever for message
        while(ipc_ptr_->NumMessagesWaiting() == 0);

        // Get message
        msg = ipc_ptr_->Recv();

        // Verify message sender
        if (msg.get_source() == EXAMPLE_WK_0_NUM)
        {
            Tap();
            wd_tap_count++;
            FswDebug::Log("Recieved response, tapped wd #%lu.\n", wd_tap_count);
        }

        // Wait for a second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
   
}