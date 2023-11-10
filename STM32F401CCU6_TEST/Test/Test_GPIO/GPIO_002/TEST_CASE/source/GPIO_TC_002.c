#include <string.h>
#include "stm32f401xx.h"
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
	LVQ_GPIO_Init(GPIOC, GPIO_PIN_13, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);

	uint8_t i = 0;

	for( ; i < 10 ; i++ )
	{
		LVQ_GPIO_TogglePinValue(GPIOC, GPIO_PIN_13);
		delay();
	}
	i++;
	i++;

	CHECK_RESULT(i, 10);
}