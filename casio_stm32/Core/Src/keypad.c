/*
 * keypad.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#include "keypad.h"

// Private Data
char keypad[4][5] = { { '1', '5', '9', 'x', ')' }, { '2', '6', '0', ':', 'C' },
		{ '3', '7', '+', '=', 'B' }, { '4', '8', '-', '(', '.' } };
static GPIO_RegDef_t *colPort[5] = { GPIOB, GPIOB, GPIOB, GPIOB, GPIOB };
static uint16_t colPin[5] = { GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5,GPIO_PIN_4, GPIO_PIN_3 };

static GPIO_RegDef_t *rowPort[4] = { GPIOA, GPIOA, GPIOA, GPIOA };
static uint16_t rowPin[4] = { GPIO_PIN_15, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2 };

#define ROW_PINS (GPIO_PIN_15 | GPIO_PIN_0 |  GPIO_PIN_1 | GPIO_PIN_2)
#define COL_PINS (GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3)

//Private function
GPIO_InitTypeDef keypad_hang = {
	.Pin = ROW_PINS,
	.Mode = GPIO_MODE_OUTPUT,
	.OType = GPIO_OTYPE_OD,
	.Pull = GPIO_PULLUP,
};

GPIO_InitTypeDef keypad_cot = {
	.Pin = COL_PINS,
	.Mode = GPIO_MODE_INPUT,
	.Pull = GPIO_PULLUP,
};

void keyPad_init(){
	GPIO_Init(GPIOA,&keypad_hang);
	GPIO_Init(GPIOB,&keypad_cot);
}

static void set_all_row_high() {
	for (int i = 0; i < 4; i++) {
		GPIO_WritePin(rowPort[i], rowPin[i], 1);
	}
}

//Public function
char keyPad_scan(void) {
	for (int i = 0; i < 4; i++) {
		set_all_row_high();
		GPIO_WritePin(rowPort[i], rowPin[i], 0);

		for (int j = 0; j < 5; j++) {
			if (GPIO_ReadPin(colPort[j], colPin[j]) == 0) {
				delay_ms(20);
				if (GPIO_ReadPin(colPort[j], colPin[j]) == 0) {
					while (GPIO_ReadPin(colPort[j], colPin[j])
							== 0) {
						delay_ms(10);
					}
					return keypad[i][j];
				}
			}
		}
	}
	return 'c';
}
