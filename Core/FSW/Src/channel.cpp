#include "channel.h"

#include "fsw_util.h"

Channel::Channel(taskid_t dest) : dest_(dest) {}

Status Channel::Init()
{
    queue_handle = xQueueCreate(DEF_QUEUE_LEN, sizeof(Message));
    send_mutex = xSemaphoreCreateMutex();

    if (!queue_handle)
    {
        return Status::ERROR;
    }

    return Status::OK;
}

Status Channel::Send(void *data, TickType_t block_time)
{
    BaseType_t ret;

    xSemaphoreTake(send_mutex, portMAX_DELAY);

    Message msg(FswUtil::GetId(), data);

    ret = xQueueSend(queue_handle, &msg, block_time);
    if (ret != pdPASS)
    {
        xSemaphoreGive(send_mutex);

        return Status::ERROR;
    }

    xSemaphoreGive(send_mutex);

    return Status::OK;
}

Message Channel::Recv(TickType_t block_time)
{
    Message msg(-1, NULL);

    xQueueReceive(queue_handle, &msg, block_time);
    return msg;
}

size_t Channel::NumMessagesWaiting()
{
    return uxQueueMessagesWaiting(queue_handle);
}
