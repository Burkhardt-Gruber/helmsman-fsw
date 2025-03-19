#include "beacon_wk.h"

BeaconWk::BeaconWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t transmit_period_ms) : Worker(ipc_ptr), transmit_period_ms_(transmit_period_ms) {}

void BeaconWk::Run(void *arg)
{
    (void)arg;

    Message msg(-1, NULL);
    taskid_t msg_source;
    TickType_t start_tick = xTaskGetTickCount();

    while(1)
    {
        // Send message to WD
        ipc_ptr_->Send(WATCHDOG_NUM, NULL, portMAX_DELAY)

        // Block for  waiting for a message for 
        msg = ipc_ptr_->Recv(WD_TIMEOUT_TICKS);

        // Check if recieved anything, or timeout
        if (msg.get_source() != -1)
        {

        }
    }
}

void FillBeaconPacket(taskid_t tid);