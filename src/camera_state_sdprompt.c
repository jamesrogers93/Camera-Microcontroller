/**
  ******************************************************************************
  * @file    camera_state_sdprompt.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Handles the camera_sdprompt_run() state.
	* 
  ******************************************************************************
	*/
#include "camera_states.h"
#include "camera_shared.h"
#include "sdcard_module.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */

/** @defgroup CAMERA_STATES_SDPROMPT
  * @{
  */
	
/** @defgroup CAMERA_STATES_SDPROMPT_Private
  * @{
  */

/**
  * @brief  The prompt message.
  */
#define PROMPT_MSG "INSERT SDCARD"

/**
  * @brief  Length of the prompt message.
  */
#define PROMPT_MSG_LEN 13

/**
  * @brief  Width in pixels of the character.
  */
#define CHAR_WIDTH 16

/**
  * @brief  The GLCD font.
  */
extern GLCD_FONT     GLCD_Font_16x24;

/**
  * @}
  */ 

/** @defgroup CAMERA_STATES_SDPROMPT_Public
  * @{
  */
	
/**
  * @brief  Prompts the user to insert the SD card.
  * @retval status: The status of the camera
	*
	* This state will prompt the user to enter an SD card if it is not detected. Once the SD card is detected, it will be 
	* reinitalised and the state will be returned to the camera_cameraview_run() state as default.
  */
uint8_t camera_sdprompt_run(void)
{
	// Check if SD card is inserted
	if(SDCard_IsDetected() == SDCARD_OK)
	{
		// SD card is inserted.
		
		// Re initalise the SD card.
		if(SDCard_Initalise() != SDCARD_OK)
		{
			return CAMERA_ERROR;
		}
		
		// Release draw to screen flag
		Camera_DrawToScreen = CAMERA_DRAWON;
		
		// Change state to the camera view as default
		camera_state_ptr = &camera_cameraview_run;
	}
	// If we are able to draw to screen
	else if(Camera_DrawToScreen == CAMERA_DRAWON)
	{
		// Capture draw to screen flag
		Camera_DrawToScreen = CAMERA_DRAWOFF;
		
		// Prompt user to insert SD card.
		GLCD_ClearScreen();
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString((GLCD_WIDTH * 0.5) - ((PROMPT_MSG_LEN*0.5) * CHAR_WIDTH), 
										(GLCD_HEIGHT * 0.5), 
										PROMPT_MSG);
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
