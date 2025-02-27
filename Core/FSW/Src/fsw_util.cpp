#include "fsw_util.h"

#include "FreeRTOS.h"
#include "task.h"

taskid_t FswUtil::GetId()
{
    return (taskid_t)pvTaskGetThreadLocalStoragePointer(NULL, 0);
}