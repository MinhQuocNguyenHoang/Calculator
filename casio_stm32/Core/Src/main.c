#include "stdio.h"
#include "app_main.h"

void System_run() {
	char choice;
	LCD_setCursor(0, 0);
	LCD_puts("1.Tinh toan");
	LCD_setCursor(1, 0);
	LCD_puts("2.Giai pt");
	while (1) {
		choice = keyPad_scan();
		if (choice != 'c') {
			if (choice == '1') {
				LCD_setCursor(0, 15);
				LCD_puts(".");
				delay_ms(500);
				LCD_clear();
				App_RunCalculatorMode();
				LCD_setCursor(0, 0);
				LCD_puts("1.Tinh toan");
				LCD_setCursor(1, 0);
				LCD_puts("2.Giai pt");

			} else if (choice == '2') {
				LCD_setCursor(1, 15);
				LCD_puts(".");
				delay_ms(500);
				LCD_clear();
				App_RunSolverMode();
				LCD_setCursor(0, 0);
				LCD_puts("1.Tinh toan");
				LCD_setCursor(1, 0);
				LCD_puts("2.Giai pt");
			}
		}
	}
}

int main(void) {
	system_stm32_init();
	gpioa_clock_enable();
	gpiob_clock_enable();
	keyPad_init();
	LCD_init();
	while (1) {
		System_run();
	}
}