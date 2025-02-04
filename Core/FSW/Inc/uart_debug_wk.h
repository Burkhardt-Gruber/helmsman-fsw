#pragma once

#include "worker.h"
#include "main.h"

/**
 * @brief Class for communicating over USART3 on the Nucleo for debugging purposes
 */
class UartDebugWk : public Worker
{
public:
    void Setup(void * arg) override;
    void Run(void *arg) override;
    ~UartDebugWk();
private:
};