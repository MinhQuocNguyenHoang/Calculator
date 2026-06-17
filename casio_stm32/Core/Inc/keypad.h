#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
#include "clock.h"
#include "gpio.h"
#include "system_stm32_init.h"

extern char keypad[4][5];

#ifdef __cplusplus
extern "C"
{
#endif
// Public Function
char keyPad_scan(void);
void keyPad_init();

#ifdef __cplusplus
}
#endif

#endif /* INC_KEYPAD_H_ */
