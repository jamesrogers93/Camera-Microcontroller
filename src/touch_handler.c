#include "Touch_Handler.h"
#include "Board_Touch.h"
#include "stm32f7xx_hal.h"

uint8_t TouchHandler_touchPosition(int *x, int *y)
{
	// Check if the display was touched
	TOUCH_STATE  tsc_state;
	Touch_GetState (&tsc_state); /* Get touch state */ 

	HAL_Delay(100);
  
	if (tsc_state.pressed) 
	{
		// Get the position of the touch and store it in the parameter, position
		*(x) = tsc_state.x;
		*(y) = tsc_state.y;
			
		return TOUCHSCREEN_TOUCHED;
	}
	
	return TOUCHSCREEN_NOT_TOUCHED;
}
