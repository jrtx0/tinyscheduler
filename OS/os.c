#include "stm32f10x.h"
#include "core_cm3.h"
#include "task.h"

// unit: MHz
#define CONFIG_SYSCLK 72
// unit: us
#define CONFIG_OS_SYSCLK_DIV 8
#define CONFIG_OS_SYSTICK_CLK (CONFIG_SYSCLK / CONFIG_OS_SYSCLK_DIV)
// 10ms
#define CONFIG_OS_TICK_TIME_US 10000

#define SYSTICK_LOAD (CONFIG_OS_TICK_TIME_US * CONFIG_OS_SYSTICK_CLK - 1)


void os_init()
{
    init_task();
}

void PendSV_init() {
    NVIC_SetPriority(PendSV_IRQn, 0xFF);
}

void SysTick_init() {
    SysTick->LOAD  = SYSTICK_LOAD;
    SysTick->VAL   = 0;
    SysTick->CTRL  = //SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;
    
    NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}

void os_start()
{
    PendSV_init();
    SysTick_init();
}
