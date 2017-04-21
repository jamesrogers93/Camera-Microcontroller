#include "Camera_View.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Camera
#include "camera_module.h"

// SDCard
#include "sdcard_module.h"

// Touch
#include "touch_handler.h"

// Buttons
#include "button_handler.h"

// JPEG
#include "jpeg_write.h"

// BMP
#include "bmp_write.h"

// Camera application
#include "camera_globals.h"
#include "../icons/icon_photos.c"
#include "error_message.h"

extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

unsigned int num_viewEntities;


void Camera_View_TakePhoto(void);

void Camera_View_Initalise(void)
{
	
}

enum CAMERA_STATE Camera_View_Run(void)
{

	// Check if we can draw to screen.
	// This prevents us from drawing the same thing to the screen every cycle.
	if(Camera_Global_DrawToScreen == CAMERA_GLOBAL_DRAWON)
	{
		// Lock the draw to screen flag.
		Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWOFF;
		
		// Draw the state string to the screen.
		/*GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Camera State");
		
		// Draw the photos icon to the screen.
		GLCD_DrawBitmap( 
										Camera_ViewEntities[0].position.x, 
										Camera_ViewEntities[0].position.y, 
										Camera_ViewEntities[0].image->width,
										Camera_ViewEntities[0].image->height, 
										Camera_ViewEntities[0].image->pixel_data);*/
		
		Camera_Resume();
	}
	
	// Check if the photos icon has been pressed.
	Point_2D point;
	if(Touch_Handler_Touched(&point.x, &point.y))
	{
		// Reset the touch timer
		Touch_Handler_Reset();
		
		// Turn off the camera
		Camera_Pause();
		
		// Clear the screen
		GLCD_ClearScreen();
			
		// Release the draw to screen flag, enabling items to be drawn again.
		Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
			
		// Return the next state.
		return CAMERA_PHOTOS;
	}
	
	// Check if the button is pressed
	if(Button_Pressed())
	{
			Camera_View_TakePhoto();
	}
	
	// Remain in the same state/
	return CAMERA_VIEW;
}

void Camera_View_TakePhoto(void)
{
	// Take a snapshot and store in buffer
	Camera_Snapshot((uint16_t *)Camera_BufferAddress());
		
	// Find the number of photos on the sdcard so we know what to name this photo
	uint16_t numFiles;
	if(SDCard_GetNumFileType(&numFiles, PHOTO_ICONDIRECTORY, "BMP", 3) != SDCARD_OK)
	{
		while(1){}
	}
		
	// Create image file names by using the count of the number of images on the SD card
	char file_jpg[30];
		
	sprintf(file_jpg, "%s/%d.jpg", PHOTO_DIRECTORY, numFiles+1);
	
	char file_bmp[30];
	sprintf(file_bmp, "%s/%d.bmp", PHOTO_ICONDIRECTORY, numFiles+1);
	
	//
	// Save the image as a JPEG
	//
		
	FIL file;
	if(SDCard_OpenFile(&file, file_jpg, FA_WRITE | FA_CREATE_NEW) != SDCARD_OK)
	{
		while(1){}
	}
		
	jpeg_write(&file, (uint8_t *)Camera_BufferAddress(), 480, 272);

	// Close the file
	if(SDCard_CloseFile(&file)!= SDCARD_OK)
	{
		while(1){}
	}
		
	//
	// Save a 48x48 bmp version of the image
	//
		
	if(SDCard_OpenFile(&file, file_bmp, FA_WRITE | FA_CREATE_NEW) != SDCARD_OK)
	{
		while(1){}
	}
		
	// Write buffer to bmp
	if(bmp_write(&file, (uint8_t *)Camera_BufferAddress(), 480, 272, 48, 48) != BMPWRITE_OK)
	{
		while(1){}
	}
		
	// Close the file
	if(SDCard_CloseFile(&file)!= SDCARD_OK)
	{
		while(1){}
	}
}
