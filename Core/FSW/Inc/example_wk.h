#pragma once

#include "worker.h"

/**
 * @brief An example worker
 */
class ExampleWk : public Worker
{
public:
    void Setup(void *arg) override;
    
private:
    void Run(void *arg) override;
};