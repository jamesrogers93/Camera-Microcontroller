/**
  ******************************************************************************
  * @file    camera_state_photopreviews.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Handles the camera_photopreviews_run() state.
	* 
  ******************************************************************************
	*/

/* Includes ------------------------------------------------------------------*/
#include "camera_state_photopreviews.h"
#include "camera_states.h"
#include "camera_shared.h"
#include "../camera_options.h"
#include <stdlib.h>
#include <string.h>
#include "sdcard_module.h"
#include "bmp_read.h"
#include "entity.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "../icons/icon_camera.c"
#include "touch_handler.h"

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_PHOTOPREVIEWS
  * @{
  */
	
/** @defgroup CAMERA_STATES_PHOTOPREVIEWS_Private
  * @{
  */

/**
  * @brief  Padding between content and the edge of the display.
  */
#define PADDING 5

/**
  * @brief  Max number of columns for image previews.
  */
#define MAX_COLUMN 10

/**
  * @brief  Max number of rows for image previews.
  */
#define MAX_ROW 4

/**
  * @brief  Image previews size.
  */
#define PREVIEW_SIZE 48

/**
  * @brief  Preview image hight padding.
  */
#define PREVIEW_HEIGHT_PADDING 40

/**
  * @brief  Preview image width padding.
  */
#define PREVIEW_WIDTH_PADDING 20

extern uint32_t photoSpecificID;

/**
  * @brief  The onscreen button.
	*
	* Used to switch back to the camera_cameraview_run() state when pressed.
  */
Entity cameraButton;

/**
  * @brief Image preview filenames.
	*
	* Stores all of the image preview file names for a row.
  */
char* fileNames[MAX_COLUMN];

/**
  * @brief Count of previews on screen.
	*
	* Stores a count of all previews on the screen. This is used when detecting 
	* collision between touch location and preview icon.
  */
uint16_t numPreviewsOnScreen1;

/**
  * @brief Draws the photo previews to screen.
  * @retval status: The status of the camera
	*/
uint8_t photopreviews_draw(void);

/**
  * @brief  Initalises the camera_photopreviews_run() state.
  * @retval status: The status of the camera
  */
uint8_t camera_photopreviews_initalise(void)
{
	cameraButton = Entity_Make(
															Point_2D_Make(
																						GLCD_WIDTH-Icon_Camera.width - PADDING, 
																						GLCD_HEIGHT-Icon_Camera.height - PADDING), 
															&Icon_Camera);
	
	// Reserve memory to store directories of row of image previews  
	int i;
	for(i = 0; i < MAX_COLUMN; i++)
	{
		fileNames[i] = (char*)malloc(MAX_FILENAME_LENGTH);
		if(fileNames[i] == NULL)
		{
			return CAMERA_ERROR;
		}
	}
	
	return CAMERA_OK;
}

/**
  * @brief Draws the photo previews to screen.
  * @retval status: The status of the camera
	*/
uint8_t photopreviews_draw(void)
{
	// Set the number of preview images on screen to 0.
	// Ready to count the preview images on screen.
	numPreviewsOnScreen1 = 0;
	
	// Loop over all rows and columns
	int i, j;
	for(i = 0; i < MAX_ROW; i++)
	{
		// Get the y coord for the row of image previews
		unsigned int y = PREVIEW_SIZE * i + PREVIEW_HEIGHT_PADDING;
		
		// Load image preview directories for this row
		unsigned int startIndex = MAX_COLUMN*i;
		uint16_t numPreviewsInRow;
		if(SDCard_GetBMPFileName(&numPreviewsInRow, PREVIEW_DIRECTORY, fileNames, MAX_COLUMN, MAX_FILENAME_LENGTH, startIndex) != SDCARD_OK)
		{
			return CAMERA_ERROR;
		}
		
		// Count the total number of previews loaded 
		numPreviewsOnScreen1 += numPreviewsInRow;
		
		// Loop over all elements in row
		for(j = 0; j < numPreviewsInRow; j++)
		{
			char path[30];
			sprintf(path, "%s/%s", PREVIEW_DIRECTORY, fileNames[j]);
			
			// Open file from SD Card
			FIL file;
			if(SDCard_OpenFile(&file, path, FA_READ) != SDCARD_OK)
			{
				return CAMERA_ERROR;
			}
			
			// Load bmp from file
			uint16_t width, height;
			if(bmp_read(&file, (uint8_t *)ImageBufferAddress(), &width, &height) != BMPREAD_OK)
			{
				return CAMERA_ERROR;
			}
			
			// Check if the image loaded is the size of a preview image specification
			if(width != PREVIEW_SIZE || height != PREVIEW_SIZE)
			{
				return CAMERA_ERROR;
			}
			
			// Close File
			if(SDCard_CloseFile(&file) != SDCARD_OK)
			{
				return CAMERA_ERROR;
			}
	
			// Get the x coord for the image in the row
			unsigned int x = PREVIEW_SIZE * j;
					
			// Draw the buffer to screen
			GLCD_DrawBitmap(x, 
											y, 
											PREVIEW_SIZE, 
											PREVIEW_SIZE, 
											(uint8_t *)ImageBufferAddress());
		}
	}

	return CAMERA_OK;
}

/**
  * @}
  */ 

/** @defgroup CAMERA_STATES_PHOTOPREVIEWS_Public
  * @{
  */

/**
  * @brief  Displays the photo preview icons from the SD card to the screen.
  * @retval status: The status of the camera
  *
	* Here the state will load the BMP preview icons from the SD card and display them to the screen.
	* This state will set the state function pointer to the camera_photospecific_run() state if an image is touched to display a 
	* fullscreen version of it. For camera_photospecific_run() to know which image to display, the photoSpecificID in camera_shared.c is set to the id of the image touched.
	* This state will set the state to camera_cameraview_run() if the camera icon is touched.
	* This state will also set the state function pointer to the camera_sdprompt_run() state if there is no SD card detected.
	*/
uint8_t camera_photopreviews_run(void)
{
	uint8_t status = CAMERA_OK;
	
	// Check if we can draw to screen.
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
			
		// Turn off draw to screen flag
		Camera_DrawToScreen = CAMERA_DRAWOFF;
		
		// Draw the previews to screen
		status = photopreviews_draw();
		
		// Draw the button icon to the screen.
		GLCD_DrawBitmap( 
										cameraButton.position.x, 
										cameraButton.position.y, 
										cameraButton.image->width,
										cameraButton.image->height, 
										cameraButton.image->pixel_data);
	}
	
	// Check if screen is touched.	
	Point_2D point;
	if(TouchHandler_touchPosition(&point.x, &point.y) == TOUCHSCREEN_TOUCHED)
	{
		
		// Check if entity is touched
		if(Entity_Point_Collision(&cameraButton, &point) != 0)
		{
							
			// Clear the screen
			GLCD_ClearScreen();
						
			// Release the draw to screen flag, enabling items to be drawn again.
			Camera_DrawToScreen = CAMERA_DRAWON;
						
			// Make cameraview the next state
			camera_state_ptr = &camera_cameraview_run;
		}
			
		// Check if picture is touched.
		int x = point.x / PREVIEW_SIZE+1;
		if(point.y > PREVIEW_HEIGHT_PADDING)
		{
			int y = ((point.y - PREVIEW_HEIGHT_PADDING) / PREVIEW_SIZE);
			if(y < MAX_ROW)
			{
				// Touched in the preview zone.
							
				// Now check if touched a image.
				int imgTouched = MAX_COLUMN * y + x;
				if(imgTouched <= numPreviewsOnScreen1)
				{
					// Collision with image.
								
					// Store the image touched.
					photoSpecificID = imgTouched;
								
					// Release the draw to screen flag, enabling items to be drawn again.
					Camera_DrawToScreen = CAMERA_DRAWON;
								
					GLCD_ClearScreen();
								
					// Switch to displaying a full image.
					camera_state_ptr = &camera_photospecific_run;
				}						
			}
		}
	}
	
	return status;
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
