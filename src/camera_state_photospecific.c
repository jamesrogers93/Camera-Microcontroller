/**
  ******************************************************************************
  * @file    camera_state_photospecific.c 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Handles the camera_photospecific_run() state.
	* 
  ******************************************************************************
	*/
	
/* Includes ------------------------------------------------------------------*/
#include "camera_states.h"
#include "camera_shared.h"
#include "../camera_options.h"
#include "sdcard_module.h"
#include "jpeg_read.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include <stdlib.h>
#include "touch_handler.h"


/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_PHOTOSPECIFIC
  * @{
  */
	
/** @defgroup CAMERA_STATES_PHOTOSPECIFIC_Private
  * @{
  */

extern uint32_t photoSpecificID;

/**
  * @brief  Draws a fullscreen JPEG image to screen.
  * @retval status: The status of the camera
  */
uint8_t drawPhoto(const uint32_t index)
{
	// Load the bmp buffer into memory from SDCard
	
	// Get the file name of the imageTouched bmp
	uint16_t numPreviewsInRow;
	char* fileName[1];
	fileName[0] = (char*)malloc(MAX_FILENAME_LENGTH);
	if(SDCard_GetBMPFileName(&numPreviewsInRow, PREVIEW_DIRECTORY, fileName, 1, MAX_FILENAME_LENGTH, index) != SDCARD_OK)
	{
		while(1){}
	}
	
	if(numPreviewsInRow != 1)
		return 0;
	
	// Change file extension to jpg
	char *charPtr = fileName[0];
	while (*(charPtr) != 0x2E) // . 
  {
		charPtr++;
  }
  *(++charPtr) = 'j'; 
	*(++charPtr) = 'p';
	*(++charPtr) = 'g';
	
	// Format the string to point to the jpg file
	char path[30];
	sprintf(path, "%s/%s", PHOTO_DIRECTORY, fileName[0]);
	
	// Open File
	FIL file;
	if(SDCard_OpenFile(&file, path, FA_READ) != SDCARD_OK)
	{
		return 0;
	}
	
	// Decode jpeg image and store in buffer
	uint16_t width, height;
	jpeg_read(&file, (uint8_t *)ImageBufferAddress(), &width, &height);
	
	// Close File
	if(SDCard_CloseFile(&file) != SDCARD_OK)
	{
		return 0;
	}
	
	// Draw Buffer
	GLCD_DrawBitmap(0, 
									0, 
									width, 
									height, 
									(uint8_t *)ImageBufferAddress());
	
	return 1;
}

/**
  * @}
  */ 

/** @defgroup CAMERA_STATES_PHOTOSPECIFIC_Public
  * @{
  */

/**
  * @brief  Displays the a fullscreen JPEG photo.
  * @retval status: The status of the camera
	*
	* Here the state will load the JPEG image specified by photoSpecificID in camera_shared.c.
	* This state will change the state to the camera_photopreviews_run() state if the screen is touched.
	* This state will also set the state function pointer to the camera_sdprompt_run() state if there is no SD card detected.
  */
uint8_t camera_photospecific_run(void)
{
	// Check if we can draw to screen.
	// This prevents us from drawing the same thing to the screen every frame.
	if(Camera_DrawToScreen == CAMERA_DRAWON)
	{
		// Check if SD card is inserted
		if(SDCard_IsDetected() != SDCARD_OK)
		{
			// Release the draw to screen flag.
			Camera_DrawToScreen = CAMERA_DRAWON;
		
			// SD card is not inserted. Set Prompt SD card as next state.
			camera_state_ptr = &camera_sdprompt_run;
		
			// Abort state
			return CAMERA_OK;
		}
		
		// Lock the draw to screen flag.
		Camera_DrawToScreen = CAMERA_DRAWOFF;
				
		// Draw the photo
		if(!drawPhoto(photoSpecificID-1))
		{
			return CAMERA_ERROR;
		}
	}
	
	int x = 0;
	int y = 0;
	if(TouchHandler_touchPosition(&x, &y) == TOUCHSCREEN_TOUCHED)
	{		
		// Release the draw to screen flag, enabling items to be drawn again.
		Camera_DrawToScreen = CAMERA_DRAWON;
								
		// Clear the screen
		GLCD_ClearScreen();
				
		// Switch state back to displaying the previews.
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

