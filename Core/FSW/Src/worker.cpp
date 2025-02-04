#include "worker.h"

Worker::Worker() {}

void Worker::TaskFunction(void *arg)
{
    Worker *wk_ptr = static_cast<Worker *>(arg);
    wk_ptr->Run(NULL);
}

void Worker::Run(void *arg)
{
    while(1);
}

Worker::~Worker() {}