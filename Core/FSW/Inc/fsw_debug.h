#pragma once

#include <chrono>

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
     * @brief Output a string over UART, with the calling function and line
     */
    static void Log(const char *format, ...);

private:
    static void USART3_SendChar(char c);
    static void USART3_SendString(const char *str);
};