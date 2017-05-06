
#ifndef _TOUCH_HANDLER_H
#define _TOUCH_HANDLER_H

#include <stdint.h>

#define TOUCHSCREEN_NOT_TOUCHED	((uint8_t)0x00)
#define TOUCHSCREEN_TOUCHED			((uint8_t)0x01)

uint8_t TouchHandler_touchPosition(int *x, int *y);

#endif /* _TOUCH_HANDLER_H */
