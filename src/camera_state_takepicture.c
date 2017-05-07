
#include "camera_states.h"
#include "camera_shared.h"
#include "../camera_options.h"
#include "camera_module.h"
#include "sdcard_module.h"
#include "jpeg_write.h"
#include "bmp_write.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"


uint8_t camera_takepicture_run(void)
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
	
	// Take a snapshot and store in buffer
	Camera_Snapshot((uint16_t *)ImageBufferAddress());
	
	Camera_Pause();
	
	// Clear screen and turn black for screen fe
	GLCD_ClearScreen();
	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		
	// Find the number of photos on the sdcard so we know what to name this photo
	uint16_t numFiles;
	if(SDCard_GetNumFileType(&numFiles, PREVIEW_DIRECTORY, "BMP", 3) != SDCARD_OK)
	{
		return CAMERA_ERROR;
	}
		
	// Create image file names by using the count of the number of images on the SD card
	char file_jpg[30];
		
	sprintf(file_jpg, "%s/%d.jpg", PHOTO_DIRECTORY, numFiles+1);
	
	char file_bmp[30];
	sprintf(file_bmp, "%s/%d.bmp", PREVIEW_DIRECTORY, numFiles+1);
	
	//
	// Save the image as a JPEG
	//
		
	FIL file;
	if(SDCard_OpenFile(&file, file_jpg, FA_WRITE | FA_CREATE_ALWAYS) != SDCARD_OK)
	{
		return CAMERA_ERROR;
	}
		
	jpeg_write(&file, (uint8_t *)ImageBufferAddress(), 480, 272);

	// Close the file
	if(SDCard_CloseFile(&file)!= SDCARD_OK)
	{
		return CAMERA_ERROR;
	}
		
	//
	// Save a 48x48 bmp version of the image
	//
		
	if(SDCard_OpenFile(&file, file_bmp, FA_WRITE | FA_CREATE_NEW) != SDCARD_OK)
	{
		return CAMERA_ERROR;
	}
		
	// Write buffer to bmp
	if(bmp_write(&file, (uint8_t *)ImageBufferAddress(), 480, 272, 48, 48) != BMPWRITE_OK)
	{
		return CAMERA_ERROR;
	}
		
	// Close the file
	if(SDCard_CloseFile(&file)!= SDCARD_OK)
	{
		return CAMERA_ERROR;
	}
	
	GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
	
	// Set the state back to camera view
	camera_state_ptr = &camera_cameraview_run;
	
	Camera_Resume();
	
	return CAMERA_OK;
}
