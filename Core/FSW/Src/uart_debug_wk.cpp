#include "uart_debug_wk.h"

#include "main.h"

// Clock at 36MHz, USART baud 115200, 
#define USARTDIV 3125

void UartDebugWk::Setup(void *arg)
{
    // Enable clock for GPIOD
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN_Msk;

    // Enable clock for USART3
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN_Msk;

    // Configure PD8 and PD9 to be AF
    GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9_Msk);
    GPIOD->MODER |= (2 << GPIO_MODER_MODER8_Pos) | (2 << GPIO_MODER_MODER9_Pos);

    // Configure AF to be USART, which is AF7
    GPIOD->AFR[1] &= ~(GPIO_AFRH_AFRH0_Msk | GPIO_AFRH_AFRH1_Msk);
    GPIOD->AFR[1] |= (7 << GPIO_AFRH_AFRH0_Pos) | (7 << GPIO_AFRH_AFRH1_Pos);

    // Set USART baud
    USART3->BRR = USARTDIV;

    // Enable USART, transmition
    USART3->CR1 |= USART_CR1_UE_Msk | USART_CR1_TE_Msk;

    uint8_t buffer[] = "swaos\n";

	// Looks like a TIM2 IRQ not letting us get out of here or some other IRQ. Also HAL_Delay fucks shit up for some reason. Maybe try asyncronous shit?
	while(1)
	{
		//vTaskDelay(pdMS_TO_TICKS(1000));
		for(int i = 0; i < 10000; i++);
		for (unsigned int i = 0; i < sizeof(buffer); i++)
		{
			while(!(USART3->ISR & USART_ISR_TC_Msk));
			USART3->TDR = buffer[i];
		}
	}
}

void UartDebugWk::Run(void *arg)
{
    uint8_t buffer[] = "swaos\n";
    
    // Looks like a TIM2 IRQ not letting us get out of here or some other IRQ. Also HAL_Delay fucks shit up for some reason. Maybe try asyncronous shit?
    while(1)
    {
        //vTaskDelay(pdMS_TO_TICKS(1000));
        taskENTER_CRITICAL();
        for(int i = 0; i < 10000; i++);
        for (unsigned int i = 0; i < sizeof(buffer); i++)
        {
            while(!(USART3->ISR & USART_ISR_TC_Msk));
            USART3->TDR = buffer[i];
        }
        taskEXIT_CRITICAL();
    }
}

UartDebugWk::~UartDebugWk() {}
