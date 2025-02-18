#include "fsw_ipc.h"

FswIpc::FswIpc()
{
    for (unsigned int i = 0; i < channel_ptr_array.size(); i++)
    {
        // Worker/task ids will start at 0 and go up incrementaly
        channel_ptr_array[i] = std::make_unique<Channel>(i);
    }
}

Status FswIpc::Init()
{
    Status status;

    for (const auto& channel_ptr : channel_ptr_array)
    {
        if ((status = channel_ptr->Init()) != Status::OK)
        {
            return status;
        }
    }

    return Status::OK;
}

Status FswIpc::Send(taskid_t dest_id, void *data)
{
    configASSERT(0 <= dest_id && dest_id < WORKER_COUNT);
    return channel_ptr_array[dest_id]->Send(data);
}

Message FswIpc::Recv()
{
    taskid_t calling_id = uxTaskGetTaskNumber(NULL);
    configASSERT(0 <= calling_id && calling_id < WORKER_COUNT);

    return channel_ptr_array[calling_id]->Recv();
}

size_t FswIpc::NumMessagesWaiting()
{
    taskid_t calling_id = uxTaskGetTaskNumber(NULL);
    configASSERT(0 <= calling_id && calling_id < WORKER_COUNT);

    return channel_ptr_array[calling_id]->NumMessagesWaiting();
}
