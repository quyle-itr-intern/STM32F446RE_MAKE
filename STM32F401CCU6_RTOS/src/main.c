#include <string.h>
#include "stm32f4xx.h"
#include "lvq_stm32f4_gpio.h"
#include "lvq_stm32f4_rtos.h"
#include "result.h"

/* task handle function */
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void task5_handler(void);
void task6_handler(void);
void task7_handler(void);
void task8_handler(void);
void idle_task(void);

extern int _write(char *ptr, int len);

int main(void)
{
	LVQ_GPIO_Init(GPIOC, GPIO_PIN_13, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_0, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_1, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_2, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_3, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_4, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_5, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	LVQ_GPIO_Init(GPIOA, GPIO_PIN_6, LVQ_GPIO_Mode_OUT, LVQ_GPIO_OType_PP, LVQ_GPIO_PuPd_NOPULL, LVQ_GPIO_Speed_High);
	
	LVQ_RTOS_CreateTask(idle_task, "idle_task", 256, 1);
	LVQ_RTOS_CreateTask(task1_handler, "task1_handler", 256, 1);
	LVQ_RTOS_CreateTask(task2_handler, "task2_handler", 256, 1);
/* 	LVQ_RTOS_CreateTask(task3_handler, "task3_handler", 256, 1);
	LVQ_RTOS_CreateTask(task4_handler, "task4_handler", 256, 1);
	LVQ_RTOS_CreateTask(task5_handler, "task5_handler", 256, 1);
	LVQ_RTOS_CreateTask(task6_handler, "task6_handler", 256, 1);
	LVQ_RTOS_CreateTask(task7_handler, "task7_handler", 256, 1);
	LVQ_RTOS_CreateTask(task8_handler, "task8_handler", 256, 1); */
	
	LVQ_RTOS_ScheduleStart();

    /* Loop forever */
	for(;;);

}

void idle_task(void)
{
	while(1)
	{

	}
}

void task1_handler(void)
{
	while(1)
	{
 		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_0);
		LVQ_RTOS_Delay(30000/TICK_PER_MS);
	}
}
void task2_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOC, GPIO_PIN_13);
		LVQ_RTOS_Delay(100/TICK_PER_MS);
	}
}
void task3_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_1);
		LVQ_RTOS_Delay(1000);
	}
}
void task4_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_2);
		LVQ_RTOS_Delay(5000);
	}
}

void task5_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_3);
		LVQ_RTOS_Delay(2000);
	}
}

void task6_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_4);
		LVQ_RTOS_Delay(3000);
	}
}

void task7_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_5);
		LVQ_RTOS_Delay(500);
	}
}

void task8_handler(void)
{
	while(1)
	{
		LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_6);
		LVQ_RTOS_Delay(450);
	}
}

