#include <string.h>
#include "stm32f4xx.h"
#include "lvq_stm32f4_gpio.h"
#include "xprintf.h"

void Delay(volatile uint32_t ms)
{
    while( ms-- )
    {}
}

extern int _write(char *ptr, int len);
extern void _write_char(uint8_t ch);

int main(void)
{
	LVQ_GPIO_Init(GPIOC, GPIO_PIN_13, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);

	xfunc_out = _write_char;

    /* Loop forever */
	for(;;)
	{
		_write("Hello\r\n", 7);
		Delay(500000);
	}

}
