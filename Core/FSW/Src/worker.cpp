#include "worker.h"

#include <memory>

Worker::Worker(std::shared_ptr<FswIpc> ipc_ptr) : ipc_ptr_(ipc_ptr) {}

void Worker::TaskFunction(void *arg)
{
    std::shared_ptr<Worker> wk_ptr(static_cast<Worker *>(arg));
    wk_ptr->Run(NULL);
}

Worker::~Worker() {}