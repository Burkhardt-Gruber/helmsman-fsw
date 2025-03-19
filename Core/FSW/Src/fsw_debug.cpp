#include "fsw_debug.h"

#include <cstring>
#include <cstdio>
#include <cstdarg>

#include "main.h"

#define USART_BAUDRATE 115200
#define USART_CLOCK 36000000  // Assuming 36 MHz APB1 clock

SemaphoreHandle_t FswDebug::log_mutex, FswDebug::send_mutex;

void FswDebug::Init()
{
    // 1. Enable clocks for GPIO and USART3
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // Enable GPIO D clock
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // Enable USART3 clock

    // 2. Configure PD8 (TX) and PD9 (RX) as Alternate Function 7 (AF7)
    GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);  // Clear mode bits
    GPIOD->MODER |= (GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);  // Set to Alternate Function mode

    GPIOD->AFR[1] |= (7 << GPIO_AFRH_AFRH0_Pos) | (7 << GPIO_AFRH_AFRH1_Pos); // AF7 for USART3
    GPIOD->OSPEEDR |= (GPIO_OSPEEDR_OSPEEDR8 | GPIO_OSPEEDR_OSPEEDR9);  // High speed
    GPIOD->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);  // No pull-up/down

    // 3. Configure USART3
    USART3->BRR = (USART_CLOCK + (USART_BAUDRATE / 2)) / USART_BAUDRATE;  // Set baud rate (approximation)
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable TX and RX
    USART3->CR1 |= USART_CR1_UE;  // Enable USART

    // 4. Wait for USART to be ready
    while (!(USART3->ISR & USART_ISR_TEACK)) {} // Wait for TX enable
    //while (!(USART3->ISR & USART_ISR_REACK)) {} // Wait for RX enable

    log_mutex = xSemaphoreCreateMutex();
    send_mutex = xSemaphoreCreateMutex();
}

void FswDebug::Log(const char *format, ...)
{
    char buff[256];
    char new_buff[512];
    va_list args;
    char *task_name;

    xSemaphoreTake(log_mutex, portMAX_DELAY);

    task_name = pcTaskGetName(NULL);

    va_start(args, format);
    vsnprintf(buff, sizeof(buff), format, args);
    va_end(args);

    snprintf(new_buff, 512, "%-20s %s\n\r", task_name, buff);
    USART3_SendString(new_buff);

    xSemaphoreGive(log_mutex);
}

void FswDebug::USART3_SendChar(char c)
{
    while (!(USART3->ISR & USART_ISR_TXE)) {} // Wait until TX buffer is empty
    USART3->TDR = c; // Send character
}

void FswDebug::USART3_SendString(const char *str)
{
    xSemaphoreTake(send_mutex, portMAX_DELAY);

    while (*str) {
        USART3_SendChar(*str++);
    }

    xSemaphoreGive(send_mutex);
}