#include "led.h"
#include "os.h"
#include "task.h"

#define STACK_LDE1_SIZE 256
#define STACK_LED2_SIZE 256

stack_t stack_led1[STACK_LDE1_SIZE];
stack_t stack_led2[STACK_LED2_SIZE];

int n1 = 0, n2 = 1;
void task_blink_led_1()
{
    for (;;)
    {
        // if GPIOC.2 == 1 then GPIOC.2 = 0
        if ((GPIOC->IDR & (1 << 2)) == (1 << 2))
        {
            GPIOC->ODR &= ~(1 << 2);
        }
        else
        {
            GPIOC->ODR |= (1 << 2);
        }
        
        n1 = n1 == 0 ? 1 : 0;
        for (int i = 0; i < 1000000; i++) ;
    }
}

void task_blink_led_2()
{
    for (;;)
    {
        // if GPIOC.3 == 1 then GPIOC.3 = 0
        if ((GPIOC->ODR & (1 << 3)) == (1 << 3))
        {
            GPIOC->ODR &= ~(1 << 3);
        }
        else
        {
            GPIOC->ODR |= (1 << 3);
        }
        
        n2 = n2 == 0 ? 1 : 0;
        for (int j = 0; j < 1000000; j++) ;
    }
}

int main(void)
{
    os_init();
 
    led_gpio_config(); 
    
    create_task(task_blink_led_1, 0, stack_led1, STACK_LDE1_SIZE);
    create_task(task_blink_led_2, 0, stack_led2, STACK_LED2_SIZE);
    
    os_start();
    
    for (;;);
}

