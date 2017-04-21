#include "Button_Handler.h"
#include "Board_Buttons.h"

#define BUTTON_DELAY 500000

static unsigned int Button_Delay = BUTTON_DELAY;

void Button_Handler_Update(void)
{
	Button_Delay++;
}

int Button_Pressed(void)
{
	// Check if the button delay is 0, meaning we are allowed to press the button
	if(Button_Delay >= BUTTON_DELAY)
	{
		// Check if the button was pressed 
		if (Buttons_GetState()) 
		{
			Button_Delay = 0;
			return 1;
		}
	}
	return 0;
}
