#include "fsw_ipc.h"

#include "fsw_debug.h"
#include "fsw_util.h"

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

Status FswIpc::Send(taskid_t dest_id, void *data, TickType_t block_time)
{
    configASSERT(0 <= dest_id && dest_id < WORKER_COUNT);
    return channel_ptr_array[dest_id]->Send(data, block_time);
}

Message FswIpc::Recv(TickType_t block_time)
{
    taskid_t calling_id = FswUtil::GetId();
    configASSERT(0 <= calling_id && calling_id < WORKER_COUNT);

    return channel_ptr_array[calling_id]->Recv(block_time);
}

size_t FswIpc::NumMessagesWaiting()
{
    taskid_t calling_id = FswUtil::GetId();
    configASSERT(0 <= calling_id && calling_id < WORKER_COUNT);

    return channel_ptr_array[calling_id]->NumMessagesWaiting();
}
