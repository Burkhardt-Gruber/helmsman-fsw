#pragma once

#include "common.h"

/**
 * @brief Util class for doing stuff.
 */
class FswUtil
{
public:
    /**
     * @brief Get the task id of the calling task
     */
    static taskid_t GetId();
};