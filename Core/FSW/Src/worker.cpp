#include "worker.h"

Worker::Worker(std::shared_ptr<FswIpc> ipc_ptr) : ipc_ptr_(ipc_ptr) {}

void Worker::TaskFunction(void *arg)
{
    struct TaskFunctionArg *tf_arg_ptr = (struct TaskFunctionArg *)arg;

    tf_arg_ptr->wk_ptr->Run(tf_arg_ptr->data);
}

Worker::~Worker() {}