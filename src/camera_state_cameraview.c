#include "camera_states.h"
#include "camera_shared.h"
#include "camera_module.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

#include "touch_handler.h"
#include "button_handler.h"

uint8_t camera_cameraview_run(void)
{
	
	// Check if we can draw to screen.
	if(Camera_DrawToScreen == CAMERA_DRAWON)
	{
	
		// Turn off draw to screen flag
		Camera_DrawToScreen = CAMERA_DRAWOFF;
		
		Camera_Resume();
	}
	
	// Check if the photos icon has been pressed.
	int x;
	int y;
	if(Touch_Handler_Touched(&x, &y))
	{
		// Reset the touch timer
		Touch_Handler_Reset();
		
		// Turn off the camera
		Camera_Pause();
		
		// Clear the screen
		GLCD_ClearScreen();
			
		// Release the draw to screen flag, enabling items to be drawn again.
		Camera_DrawToScreen = CAMERA_DRAWON;
			
		// Set the previews state as the next state.
		camera_state_ptr = &camera_photopreviews_run;
		
	// Check if the button is pressed
	}else if(Button_Pressed())
	{
		// Turn off the camera
		Camera_Pause();
		
		// Release the draw to screen flag, enabling items to be drawn again.
		Camera_DrawToScreen = CAMERA_DRAWON;
		
		// Set the take picture state as the next
		camera_state_ptr = &camera_takepicture_run;
	}
	
	return CAMERA_OK;
}
