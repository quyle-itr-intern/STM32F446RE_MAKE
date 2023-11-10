/**
  ******************************************************************************

  RTOS For STM32FRE401CCU6
  Author:   LVQ
  Updated:  31 July 2023

  ******************************************************************************
*/

#ifndef __RTOS_H
#define __RTOS_H

/**
 * @defgroup LVQ_RTOS_Typedefs
 * @brief    Library Typedefs
 * @{
 */ 
 
#include "lvq_stm32f4_rccConfig.h"
#include "lvq_stm32f4_gpio.h"
 
#define TICK_PER_MS				 1.025 + 1
#define DUMMY_XPSR  			 0x01000000U
#define MAX_TASKS                10U
#define TASK_RUNNING_STATE       0x00U
#define TASK_BLOCKED_STATE       0xFFU
#define SRAM_START               0x20000000U
#define SIZE_SRAM                ((64U) * (1024)) - 4             /* 64 Kbytes of SRAM */
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM))

#define SIZE_TASK_STACK     	 1024U
#define SIZE_SCHED_STACK    	 1024U

#define TICK_HZ 				 1000U
#define HSI_CLOCK 				 16000000U
#define SYSTICK_TIM_CLK 		 HSI_CLOCK

typedef struct
{
	uint32_t u32size_stack;
	uint32_t u32psp_value;
	uint32_t u32block_count;
	uint8_t  u8current_state;
	void (*Task_Handler) (void);
} LVQ_RTOS_TaskInfor_t;

typedef void * LVQ_RTOS_TaskHandle_t;

typedef enum
{	
	LVQ_RTOS_Status_Error,
	LVQ_RTOS_Status_Ok,
}LVQ_RTOS_Status_t;

LVQ_RTOS_Status_t LVQ_RTOS_CreateTask(LVQ_RTOS_TaskHandle_t LVQ_TaskHandler, char * LVQ_TaskName, uint32_t LVQ_TaskSize, uint32_t LVQ_TaskPriority);
void LVQ_RTOS_Delay(uint32_t tick_count);
void LVQ_RTOS_ScheduleStart(void);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#endif