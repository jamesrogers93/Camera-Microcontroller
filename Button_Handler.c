#include "Button_Handler.h"

#define BUTTON_DELAY 500000
static unsigned int Button_Delay = BUTTON_DELAY;

void Button_Handler_Update(void)
{
	Button_Delay++;
}

int Button_Pressed()
{
	// Check if the button delay is 0, meaning we are allowed to press the button
	if(Button_Delay >= BUTTON_DELAY)
	{
		// Check if the button was pressed 
		if (Buttons_GetState()) 
		{
			return 1;
		}
	}
	
	return 0;
}