#include "worker.h"

#include "common.h"

/**
 * @brief Worker which periodically transmits basic telemetry to the ground
 */
class BeaconWk : public Worker
{
public:
    BeaconWk(std::shared_ptr<FswIpc> ipc_ptr, uint32_t transmit_period_ms);

protected:
    // Packet for beacon 
    struct BeaconPacket
    {
        // ms since mission start. Updated prior to Broadcast
        uint32_t timestamp;

        uint32_t sample_1_data;

        uint32_t sample_2_data;
    } __attribute_((packed));

    struct BeaconPacket beacon_packet_;

    uint32_t transmit_period_ms_;

private:
    void Run(void *arg) override;

    void FillBeaconPacket(taskid_t tid);

    virtual void Broadcast(void *arg) = 0;
};