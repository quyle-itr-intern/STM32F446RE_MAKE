#include "Run.h"
#include <stdio.h>
#include "stm32f446xx.h"
#include "lvq_stm32f4_gpio.h"
#include "lvq_stm32f4_exti.h"

int _write(char *ptr, int len){
    int i;
    for (i =0; i<len; i++){
        while(!(USART2->SR & USART_SR_TXE)){}

        // Write to transmit data register
        USART2->DR = (*ptr++ & 0xFF);
    }
    return len;
}

void Delay(volatile uint32_t ms)
{
    while( ms-- )
    {}
}


void LVQ_EXTI_Handler(uint16_t GPIO_Pin);

void Loop(void)
{
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_5, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	
	if(LVQ_EXTI_Init(GPIOC, GPIO_PIN_13, LVQ_EXTI_Trigger_Falling) != LVQ_EXTI_Result_Ok)
		LVQ_GPIO_SetPinLow(GPIOA, GPIO_PIN_5);
	else
		LVQ_GPIO_SetPinHigh(GPIOA, GPIO_PIN_5);

	LVQ_EXTI_Handler_Set_CallBack(LVQ_EXTI_Handler);
	
	while (1) 
	{
        _write("Hello There (-.-)\n\r", 19);
        Delay(1000000);
		LVQ_GPIO_SetPinLow(GPIOA, GPIO_PIN_5);
		Delay(1000000);
		LVQ_GPIO_SetPinHigh(GPIOA, GPIO_PIN_5);
		Delay(1000000);
    }
	
}

void LVQ_EXTI_Handler(uint16_t GPIO_Pin) 
{
	/* Handle external line 13 interrupts */
	if (GPIO_Pin == GPIO_PIN_13) 
	{ 
		Delay(1000000/4);
			_write("Exit\n\r", 6);
			LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_5);
	}
}
