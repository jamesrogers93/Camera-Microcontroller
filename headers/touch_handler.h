
#ifndef _TOUCH_HANDLER_H
#define _TOUCH_HANDLER_H

#include <stdint.h>

void Touch_Handler_Update(void);
void Touch_Handler_Reset(void);
uint8_t Touch_Handler_Touched(int *x, int *y);

#endif /* _TOUCH_HANDLER_H */
