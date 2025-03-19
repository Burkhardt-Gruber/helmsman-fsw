#pragma once

#include <cstdint>

#include "FreeRTOS.h"

// 3 second timeout
#define WD_TIMEOUT_MS 3000
#define WD_TIMEOUT_TICKS pdMS_TO_TICKS(WD_TIMEOUT_MS)

// Status
enum class Status
{
    OK = 0,
    ERROR = 1
};

// Typedef for identifying tasks
typedef int32_t taskid_t;