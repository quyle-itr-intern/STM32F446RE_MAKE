/**
  ******************************************************************************

  RTOS For STM32FRE401CCU6
  Author:   LVQ
  Updated:  31 July 2023

  ******************************************************************************
*/

#include "lvq_stm32f4_rtos.h"

/* Function */
uint32_t LVQ_RTOS_CaculatorStack(uint8_t TaskCreate);
void LVQ_RTOS_ScheduleStart();
__attribute__((naked)) void LVQ_Init_Scheduler_Stack(uint32_t sched_top_of_stack);
void LVQ_RTOS_Systick_Timer(uint32_t tick_hz);
void LVQ_Schedule_Task(void);
__attribute__((naked)) void LVQ_RTOS_SP_To_PSP(void);
uint32_t get_psp_value(void);
void save_psp_value(uint32_t current_psp_value);
void update_next_task(void);
void LVQ_Update_Global_Tick_Count(void);
void LVQ_Unblock_Tasks(void);

LVQ_RTOS_TaskInfor_t user_tasks[MAX_TASKS];

uint8_t curent_task = 1;
uint32_t g_tick_count = 0;
uint8_t TaskCreate = 0;

void LVQ_RTOS_Enable_Processor_Faults(void)
{
	// 1 enable all config exception like usage foult, mem manager fault and bus fault
	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= ( 1 << 16); //mem manage
	*pSHCSR |= ( 1 << 17); //bus fault
	*pSHCSR |= ( 1 << 18); //usage fault
}

uint32_t LVQ_RTOS_CaculatorStack(uint8_t TaskCreate)
{
	uint32_t u32addresstack = SRAM_END;
	for(uint8_t i = 0; i < TaskCreate; i++)
	{
		u32addresstack -= user_tasks[i].u32size_stack;
	}
	return u32addresstack;
}

__attribute__((naked)) void LVQ_RTOS_ScheduleStart(void)
{	
	LVQ_Init_Scheduler_Stack(LVQ_RTOS_CaculatorStack(TaskCreate));
	LVQ_RTOS_Systick_Timer(TICK_HZ);
	LVQ_RTOS_SP_To_PSP();
	user_tasks[1].Task_Handler();
}

LVQ_RTOS_Status_t LVQ_RTOS_CreateTask(LVQ_RTOS_TaskHandle_t LVQ_TaskHandler, char * LVQ_TaskName, uint32_t LVQ_TaskSize, uint32_t LVQ_TaskPriority)
{	
	if(TaskCreate == 0)
	{
		/* Enable processor faults */
		LVQ_RTOS_Enable_Processor_Faults();
	}
	if(TaskCreate > MAX_TASKS)
			return LVQ_RTOS_Status_Error;
	/* Init Process Stack Value */
	user_tasks[TaskCreate].u32psp_value = LVQ_RTOS_CaculatorStack(TaskCreate);
	/* Init Current Task */
	user_tasks[TaskCreate].u8current_state = TASK_RUNNING_STATE;
	/* Init Task Handler */
	user_tasks[TaskCreate].Task_Handler = LVQ_TaskHandler;
	/* Init Size Task Handler */
	user_tasks[TaskCreate].u32size_stack = LVQ_TaskSize;
	
	uint32_t *pPSP;

	pPSP = (uint32_t*) user_tasks[TaskCreate].u32psp_value;

	pPSP--;
	*pPSP = DUMMY_XPSR;

	pPSP--; /* PC */
	*pPSP = (uint32_t) user_tasks[TaskCreate].Task_Handler;

	pPSP--; /* LR */ 
	*pPSP = 0xFFFFFFFD;

	/* R0 -> R12 */
	for(int j = 0 ; j < 13 ; j++)
	{
		pPSP--;
		*pPSP = 0;
	}
	user_tasks[TaskCreate].u32psp_value = (uint32_t)pPSP;

	TaskCreate++;
	
	return LVQ_RTOS_Status_Ok;
}

__attribute__((naked)) void LVQ_Init_Scheduler_Stack(uint32_t sched_top_of_stack)
{
    __asm volatile("MSR MSP,%0": : "r" (sched_top_of_stack) : );
    __asm volatile("BX LR"); 
}

void LVQ_RTOS_Systick_Timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t *)0xE000E014;
	uint32_t *pSCSR = (uint32_t *)0xE000E010;

	// reload value
	uint32_t count_value = (SYSTICK_TIM_CLK / TICK_HZ) - 1;
	// xóa SVR 24 bit
	*pSRVR &=~ (0x00FFFFFFFF);
	// ghi value vào SVR
	*pSRVR |= count_value;
	// enable systick exception request
	*pSCSR |= ( 1<< 1);
	// clock source
	*pSCSR |= ( 1<< 2);
	// anable counter
	*pSCSR |= ( 1<< 0);
}

void LVQ_RTOS_Delay(uint32_t tick_count)
{
	__disable_irq();
	if(curent_task)
	{
		
		user_tasks[curent_task].u32block_count = g_tick_count + tick_count;
		user_tasks[curent_task].u8current_state = TASK_BLOCKED_STATE;
		LVQ_Schedule_Task();
	}
	__enable_irq();
}

void LVQ_Schedule_Task(void)
{
	uint32_t *pICSR = (uint32_t*)0xE000ED04;
	//pend the pendsv exception
	*pICSR |= ( 1 << 28);
}

__attribute__((naked)) void LVQ_RTOS_SP_To_PSP(void)
{
	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL get_psp_value"); 
	__asm volatile ("MSR PSP,R0"); 
	__asm volatile ("POP {LR}"); 

	__asm volatile ("MOV R0,#0X02");
	__asm volatile ("MSR CONTROL,R0");
	__asm volatile ("BX LR");
}

uint32_t get_psp_value(void)
{
	return user_tasks[curent_task].u32psp_value;
}

void save_psp_value(uint32_t current_psp_value)
{
	user_tasks[curent_task].u32psp_value = current_psp_value;
}

void update_next_task(void)
{
	int state = TASK_BLOCKED_STATE;

	for( int i = 0; i < (TaskCreate); i++ )
	{
		curent_task++;
		curent_task %= TaskCreate;
		state = user_tasks[curent_task].u8current_state;
		if( (state == TASK_RUNNING_STATE) && (curent_task != 0) )
			break;
	}

	if(state != TASK_RUNNING_STATE)
	curent_task = 0;
}

void LVQ_Update_Global_Tick_Count(void)
{
	g_tick_count++;
}

void LVQ_Unblock_Tasks(void)
{
	for(int i = 1 ; i < TaskCreate ; i++)
	{
		if(user_tasks[i].u8current_state != TASK_RUNNING_STATE)
		{
			if(user_tasks[i].u32block_count == g_tick_count)
			{
				user_tasks[i].u8current_state =  TASK_RUNNING_STATE;
			}
		}
	}
}

void SysTick_Handler(void)
{
 	uint32_t *pICSR = (uint32_t*)0xE000ED04;
	LVQ_Update_Global_Tick_Count();
	LVQ_Unblock_Tasks();
	//pend the pendsv exception
	*pICSR |= ( 1 << 28);
	LVQ_GPIO_TogglePinValue(GPIOA, GPIO_PIN_1);
}

__attribute__((naked)) void PendSV_Handler(void)
{
	//* lưu trạng thái cho task current
	//1 get giá trị PSP của task đang chạy hiện tại
	__asm volatile("MRS R0, PSP");

	//2 sử dụng giá trị PSP lưu SF2 ( R4 - R11)
	__asm volatile ("STMDB R0!, {R4-R11}");

	__asm volatile("PUSH {LR}");

	//3. lưu giá trị hienj tại của PSP
	__asm volatile ("BL save_psp_value");


	//* truy xuất ngữ cảnh của Task tiếp theo
	//1 quyết định task nào chạy
	__asm volatile("BL update_next_task");

	//2. get PSP value
	__asm volatile ("BL get_psp_value");

	//3 sử dụng PSP value để truy xuát SF2 (R4 - R11)
	__asm volatile ("LDMIA R0!, {R4-R11}");

	//4. update PSP và thoát
	__asm volatile ("MSR PSP,R0");

	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}
