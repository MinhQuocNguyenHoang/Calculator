/*
 * LCD_driver.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

/*
 * LCD_casio.c
 *
 *  Created on: Oct 3, 2025
 *      Author: ADMIN
 */
#include "LCD_driver.h"
#include "system_stm32_init.h"
#include "gpio.h"

#define D4_Pin GPIO_PIN_5
#define D5_Pin GPIO_PIN_6
#define D6_Pin GPIO_PIN_7
#define D7_Pin GPIO_PIN_0
#define RS_Pin GPIO_PIN_3
#define EN_Pin GPIO_PIN_4
int row = 0;
int col = 0;

/* Prototype */
static void LCD_sendNibble_BareMetal(uint8_t data);

GPIO_InitTypeDef lcd = {
	.Pin = D4_Pin | D5_Pin | D6_Pin | D7_Pin | RS_Pin | EN_Pin,
	.Mode = GPIO_MODE_OUTPUT,
	.OType = GPIO_OTYPE_PP,
	.Speed = GPIO_SPEED_LOW,
};
// Privte function
static void LCD_sendNibble_BareMetal(uint8_t data) {
	GPIO_WritePin(GPIOA, D4_Pin,
			(data & 0x01) ? 1 : 0);
	GPIO_WritePin(GPIOA, D5_Pin,
			(data & 0x02) ? 1 : 0);
	GPIO_WritePin(GPIOA, D6_Pin,
			(data & 0x04) ? 1 : 0);
	GPIO_WritePin(GPIOB, D7_Pin,
			(data & 0x08) ? 1 : 0);

	GPIO_WritePin(GPIOA, EN_Pin, 1);
	delay_ms(1);
	GPIO_WritePin(GPIOA, EN_Pin, 0);
}

static void LCD_sendNibble(uint8_t data) {
	GPIO_WritePin(GPIOA, D4_Pin,
			(data & 0x01) ? 1 : 0);
	GPIO_WritePin(GPIOA, D5_Pin,
			(data & 0x02) ? 1 : 0);
	GPIO_WritePin(GPIOA, D6_Pin,
			(data & 0x04) ? 1 : 0);
	GPIO_WritePin(GPIOB, D7_Pin,
			(data & 0x08) ? 1 : 0);
	GPIO_WritePin(GPIOA, EN_Pin, 1);
	delay_ms(5);
	GPIO_WritePin(GPIOA, EN_Pin, 0);
}

static void LCD_sendByte(uint8_t data) {
	LCD_sendNibble(data >> 4);
	LCD_sendNibble(data);
}

static void LCD_sendByte_BareMetal(uint8_t data) {
	LCD_sendNibble_BareMetal(data >> 4);
	LCD_sendNibble_BareMetal(data);
}

static void LCD_sendCmd(uint8_t data) {
	GPIO_WritePin(GPIOA, RS_Pin, 0);
	LCD_sendByte(data);
}

// Public function
void LCD_init() {
	GPIO_InitTypeDef lcd_a = {
		.Pin = D4_Pin | D5_Pin | D6_Pin | RS_Pin | EN_Pin,
		.Mode = GPIO_MODE_OUTPUT,
		.OType = GPIO_OTYPE_PP,
		.Speed = GPIO_SPEED_LOW,
	};
	GPIO_InitTypeDef lcd_b = {
		.Pin = D7_Pin,
		.Mode = GPIO_MODE_OUTPUT,
		.OType = GPIO_OTYPE_PP,
		.Speed = GPIO_SPEED_LOW,
	};
	GPIO_Init(GPIOA,&lcd_a);
	GPIO_Init(GPIOB,&lcd_b);
	delay_ms(5);

	GPIO_WritePin(GPIOA, RS_Pin, 0);
	LCD_sendByte_BareMetal(0x33);
	LCD_sendByte_BareMetal(0x32);
	LCD_sendByte_BareMetal(0x28);
	LCD_sendByte_BareMetal(0x06);
	LCD_sendByte_BareMetal(0x0C);
	LCD_sendByte_BareMetal(0x01);
	delay_ms(2);
}

void LCD_clear() {
	LCD_sendCmd(0x01);
	delay_ms(5);
}

void LCD_setCursor(char row, char col) {
	char val = (row == 0) ? 0x00 : 0x40;
	val += col;
	LCD_sendCmd(0x80 | val);
}

void LCD_sendChar(uint8_t data) {
	GPIO_WritePin(GPIOA, RS_Pin, 1);
	LCD_sendByte(data);
}

void LCD_puts(char *data) {
	while (data[0] != '\0') {
		LCD_sendChar(data[0]);
		data++;
	}
}

void LCD_scroll(char isScroll) {
	if (isScroll) {
		LCD_sendCmd(0x04 | 0x01);
	}
}

