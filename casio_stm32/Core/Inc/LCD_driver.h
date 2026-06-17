/*
 * LCD_driver.h
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#ifndef INC_LCD_DRIVER_H_
#define INC_LCD_DRIVER_H_
#include "clock.h"
#include "gpio.h"

extern int col;
extern int row;

#ifdef __cplusplus
extern "C"
{
#endif
void LCD_clear();
void LCD_setCursor(char row, char col);
void LCD_puts(char *data);
void LCD_scroll(char isScroll);
void LCD_init();
void LCD_sendChar(uint8_t data);
#ifdef __cplusplus

}
#endif

#endif /* INC_LCD_DRIVER_H_ */
