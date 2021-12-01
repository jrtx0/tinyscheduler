#include <stdint.h>
#include "os.h"
#include "core_cm3.h"
#include "task.h" 

uint16_t current_task_id = 0;
uint16_t next_task_id = 0;

#define STACK_IDLE_SIZE 32
stack_t stack_idle[STACK_IDLE_SIZE];

#define CONFIG_MAX_TASK_NUM 8
Task_Control_Block tcb_list[CONFIG_MAX_TASK_NUM];

Task_Control_Block *current_TCB;

void init_task()
{
    create_task(task_idle, 0, stack_idle, STACK_IDLE_SIZE);
    
    current_TCB = &tcb_list[0];
    
    // for task first 
    __asm {
        MOV R0, 0x0
        MSR PSP, R0
    }
}

uint16_t create_task(void *function, void *arguments, stack_t *stack, uint16_t stack_size)
{
    if (next_task_id > CONFIG_MAX_TASK_NUM)
    {
        return 0;
    }
    
    stack_t *stack_top = &stack[stack_size];
    
    // auto save by Cortex-M3
    *(--stack_top) = (stack_t)0x01000000u; // xPSR bit 24 = 1
    *(--stack_top) = (stack_t)function;    // PC(R15) function entry point
    *(--stack_top) = (stack_t)0x14141414u; // R14 LR
    *(--stack_top) = (stack_t)0x12121212u; // R12
    *(--stack_top) = (stack_t)0x03030303u; // R3
    *(--stack_top) = (stack_t)0x02020202u; // R2
    *(--stack_top) = (stack_t)0x01010101u; // R1
    *(--stack_top) = (stack_t)arguments;   // R0
    
    // manual save by developer
    *(--stack_top) = (stack_t)0x11111111u; // R11
    *(--stack_top) = (stack_t)0x10101010u; // R10
    *(--stack_top) = (stack_t)0x09090909u; // R9
    *(--stack_top) = (stack_t)0x08080808u; // R8
    *(--stack_top) = (stack_t)0x07070707u; // R7
    *(--stack_top) = (stack_t)0x06060606u; // R6
    *(--stack_top) = (stack_t)0x05050505u; // R5
    *(--stack_top) = (stack_t)0x04040404u; // R4
    
    tcb_list[next_task_id].stack = stack_top;
    
    return next_task_id++;
}

void switch_current_TCB()
{
    if (current_task_id >= next_task_id - 1)
    {
        // if not create any task, switch to idle task
        if (next_task_id < 2) 
        {
            current_task_id = 0;
        }
        else // switch to first task
        {
            current_task_id = 1;
        }
    }
    else // switch to next task till the last
    {
        current_task_id++;
    }
    
    current_TCB = &tcb_list[current_task_id];
}

void switch_task() 
{
    // set pendsv
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void SysTick_Handler(void) 
{
    switch_task();
}

void task_idle()
{
    for (;;)
    {
        
    }
}
