#pragma once

#include "worker.h"

/**
 * @brief Worker for the gyroscope
 */
class GyroWk : public Worker
{
private:
    void Run();
};