#include "gpio.h"

void GPIO_Init(GPIO_RegDef_t *GPIOx,
               GPIO_InitTypeDef *cfg)
{
    for(uint8_t pin = 0; pin < 16; pin++)
    {
        if(!(cfg->Pin & (1U << pin)))
            continue;

        /* MODER */

        GPIOx->MODER &= ~(3U << (pin * 2));
        GPIOx->MODER |= ((uint32_t)cfg->Mode << (pin * 2));

        /* OTYPER */

        GPIOx->OTYPER &= ~(1U << pin);
        GPIOx->OTYPER |= ((uint32_t)cfg->OType << pin);

        /* OSPEEDR */

        GPIOx->OSPEEDR &= ~(3U << (pin * 2));
        GPIOx->OSPEEDR |= ((uint32_t)cfg->Speed << (pin * 2));

        /* PUPDR */

        GPIOx->PUPDR &= ~(3U << (pin * 2));
        GPIOx->PUPDR |= ((uint32_t)cfg->Pull << (pin * 2));

        /* AFR */

        if(cfg->Mode == GPIO_MODE_AF)
        {
            uint8_t afr_idx = pin / 8;
            uint8_t afr_pos = (pin % 8) * 4;

            GPIOx->AFR[afr_idx] &= ~(0xFU << afr_pos);
            GPIOx->AFR[afr_idx] |=
                ((uint32_t)cfg->Alternate << afr_pos);
        }
    }
}

void GPIO_WritePin(GPIO_RegDef_t *GPIOx,
                   uint16_t Pin,
                   uint8_t State)
{
    if(State)
    {
        GPIOx->BSRR = Pin;
    }
    else
    {
        GPIOx->BRR = Pin;
    }
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx,
                     uint16_t Pin)
{
    return ((GPIOx->IDR & Pin) != 0);
}

void GPIO_TogglePin(GPIO_RegDef_t *GPIOx,
                    uint16_t Pin)
{
    GPIOx->ODR ^= Pin;
}