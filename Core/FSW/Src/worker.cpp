#include "worker.h"

Worker::Worker() {}

void Worker::TaskFunction(void *task_parameters)
{
    RunLogic();

    // Should never reach here.
    while(1);
}