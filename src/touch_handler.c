#include "Touch_Handler.h"
#include "Board_Touch.h"

#define TOUCH_DELAY 500000

static unsigned int Touch_Delay = TOUCH_DELAY;

void Touch_Handler_Update(void)
{
	Touch_Delay++;
}

void Touch_Handler_Reset(void)
{
	Touch_Delay = 0;
}

uint8_t Touch_Handler_Touched(int *x, int *y)
{
	// Check if the touch delay is 0, meaning we are allowed to touch the display
	if(Touch_Delay >= TOUCH_DELAY)
	{
		// Check if the display was touched
		TOUCH_STATE  tsc_state;
		Touch_GetState (&tsc_state); /* Get touch state */   
		if (tsc_state.pressed) 
		{
			// Get the position of the touch and store it in the parameter, position
			*(x) = tsc_state.x;
			*(y) = tsc_state.y;
			
			return 1;
		}
	}
	
	return 0;
}
