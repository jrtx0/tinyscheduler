#ifndef __OS_H
#define __OS_H

#include "stm32f10x.h"
#include "core_cm3.h"

extern void os_init(void);
extern void os_start(void);
extern void PendSV_init(void);
extern void SysTick_init(void);

#endif /* __OS_H */
