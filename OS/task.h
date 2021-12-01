#ifndef __TASK_H
#define __TASK_H

#include <stdint.h>

typedef uint32_t stack_t;

typedef struct {
    void *stack;
} Task_Control_Block;

extern void init_task(void);
extern uint16_t create_task(void* function, void* arguments, stack_t *stack, uint16_t stack_size);
extern void task_idle(void);

#endif /* __TASK_H */
