/**
  ******************************************************************************
  * @file    camera_state_cameraview.c 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Defines the camera_cameraview_run() state
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "camera_states.h"
#include "camera_shared.h"
#include "camera_module.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "touch_handler.h"

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_CAMERAVIEW
  * @{
  */
	
/** @defgroup CAMERA_STATES_CAMERAVIEW_Public
  * @{
  */
	
/**
  * @brief  Displays the camera to the screen.
  * @retval status: The status of the camera
	*
	* Here the output from the camera is displayed fullscreen.
	* This state will set the state to camera_takepicture_run() if the button is pressed.
	* This state will set the state to camera_photopreviews_run() if the screen is touched. 
  */
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
	if(TouchHandler_touchPosition(&x, &y) == TOUCHSCREEN_TOUCHED)
	{
		// Turn off the camera
		Camera_Pause();
			
		// Clear the screen
		GLCD_ClearScreen();
				
		// Release the draw to screen flag, enabling items to be drawn again.
		Camera_DrawToScreen = CAMERA_DRAWON;
				
		// Set the previews state as the next state.
		camera_state_ptr = &camera_photopreviews_run;
	}
	
	return CAMERA_OK;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 
