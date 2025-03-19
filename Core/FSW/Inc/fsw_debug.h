#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/**
 * @brief Class for debugging stuff
 */
class FswDebug
{
public:
    /**
     * @brief Function to initialize debug
     */
    static void Init();

    /**
     * @brief Output a string over UART, with the calling function and line (TODO)
     */
    static void Log(const char *format, ...);

    static void USART3_SendString(const char *str);

private:
    static void USART3_SendChar(char c);

    static SemaphoreHandle_t log_mutex, send_mutex;
};