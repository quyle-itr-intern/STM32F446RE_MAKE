#include <string.h>
#include "stm32f446xx.h"
#include "lvq_stm32f4_gpio.h"
#include "result.h"

#define HIGH 1
#define LOW 0

void delay(void)
{
	// this will introduce ~200ms delay when system clock is 16MHz
	for (uint32_t i = 0; i < 500000 / 2; i++)
		;
}

/****************************************************************************************
 *                           Prototypes of the startup file
 *****************************************************************************************/

/****************************************************************************************
 *                           Prototypes of my application
 *****************************************************************************************/

/*************************************************************************************************
 *                            Start with my code
 **************************************************************************************************/
void gpio_TC_002(void)
{
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_5, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);

	int i = 0;
	
	volatile uint8_t a[10];

	for( ; i < 10 ; i++ )
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_5);
		delay();
	}

	CHECK_RESULT(i, 10);
}