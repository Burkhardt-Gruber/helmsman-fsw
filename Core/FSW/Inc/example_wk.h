#pragma once

#include "worker.h"

/**
 * @brief An example worker
 */
class ExampleWk : public Worker
{
public:
    ExampleWk(std::shared_ptr<FswIpc> ipc_ptr);

    void Init(void *arg) override;
    
private:
    void Run(void *arg) override;
};