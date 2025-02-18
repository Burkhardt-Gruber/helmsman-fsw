#pragma once

#include <cstdint>

// Status
enum class Status
{
    OK = 0,
    ERROR = 1
};

// Typedef for identifying tasks
typedef int32_t taskid_t;