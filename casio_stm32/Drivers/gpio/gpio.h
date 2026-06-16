#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_AF,
    GPIO_MODE_ANALOG
} GPIO_Mode_t;

typedef enum
{
    GPIO_OTYPE_PP = 0,
    GPIO_OTYPE_OD
} GPIO_OType_t;

typedef enum
{
    GPIO_NOPULL = 0,
    GPIO_PULLUP,
    GPIO_PULLDOWN
} GPIO_Pull_t;

typedef enum
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH
} GPIO_Speed_t;

typedef struct
{
    uint32_t Pin;

    GPIO_Mode_t Mode;
    GPIO_OType_t OType;
    GPIO_Pull_t Pull;
    GPIO_Speed_t Speed;

    uint8_t Alternate;
} GPIO_InitTypeDef;

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
    volatile uint32_t BRR;
} GPIO_RegDef_t;


/* GPIO BASE */

#define GPIOA_BASE     0x48000000UL
#define GPIOB_BASE     0x48000400UL
#define GPIOC_BASE     0x48000800UL
#define GPIOD_BASE     0x48000C00UL
#define GPIOF_BASE     0x48001400UL

#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASE)


/* PIN MASK */

#define GPIO_PIN_0     (1U << 0)
#define GPIO_PIN_1     (1U << 1)
#define GPIO_PIN_2     (1U << 2)
#define GPIO_PIN_3     (1U << 3)
#define GPIO_PIN_4     (1U << 4)
#define GPIO_PIN_5     (1U << 5)
#define GPIO_PIN_6     (1U << 6)
#define GPIO_PIN_7     (1U << 7)
#define GPIO_PIN_8     (1U << 8)
#define GPIO_PIN_9     (1U << 9)
#define GPIO_PIN_10    (1U << 10)
#define GPIO_PIN_11    (1U << 11)
#define GPIO_PIN_12    (1U << 12)
#define GPIO_PIN_13    (1U << 13)
#define GPIO_PIN_14    (1U << 14)
#define GPIO_PIN_15    (1U << 15)

void GPIO_Init(GPIO_RegDef_t *GPIOx,
               GPIO_InitTypeDef *GPIO_InitStruct);

void GPIO_WritePin(GPIO_RegDef_t *GPIOx,
                   uint16_t Pin,
                   uint8_t State);

uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx,
                     uint16_t Pin);

void GPIO_TogglePin(GPIO_RegDef_t *GPIOx,
                    uint16_t Pin);

#endif