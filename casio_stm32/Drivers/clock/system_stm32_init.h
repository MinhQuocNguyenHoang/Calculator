#ifndef __SYSTEM_STM32_H__
#define __SYSTEM_STM32_H__

#include <stdint.h>

/* Clock frequency */
#define SYSCLK_FREQ_HZ   48000000U
#define HCLK_FREQ_HZ     48000000U
#define PCLK1_FREQ_HZ    24000000U
#define PCLK2_FREQ_HZ    48000000U

/* System init */
void system_stm32_init(void);

/* SysTick / delay */
void systick_init(void);
void delay_ms(uint32_t ms);
uint32_t millis(void);

#endif /*__SYSTEM_STM32_H__*/