#include "Camera_View.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Camera
#include "Camera_Module.h"

// SDCard
#include "SDCard_Module.h"

// Touch
#include "Touch_Handler.h"

// Buttons
#include "Button_Handler.h"

// JPEG
#include "Jpeg_Write.h"

// BMP
#include "Bmp_Write.h"

// Camera application
#include "Camera_Defines.h"
#include "Camera_Globals.h"
#include "Icons/Icon_Photos.c"
#include "Error_Message.h"

extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

Entity Camera_ViewEntities[1];
unsigned int num_viewEntities;


void Camera_View_TakePhoto(void);

void Camera_View_Initalise(void)
{
	
	Camera_ViewEntities[0] = Entity_Make(
																				Point_2D_Make(
																											GLCD_CAMERA_WIDTH-Icon_Photos.width - GLCD_CAMERA_EDGE_PADDING, 
																											GLCD_CAMERA_HEIGHT-Icon_Photos.height - GLCD_CAMERA_EDGE_PADDING), 
																				&Icon_Photos);
	num_viewEntities = 1;
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
	if(Screen_Touched(&point))
	{
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
	Camera_Snapshot((uint8_t *)Camera_BufferAddress());
		
	// Find the number of photos on the sdcard so we know what to name this photo
	uint16_t numFiles = SDCard_GetNumFileType(PHOTO_ICONDIRECTORY, "BMP", 3);
		
	// Create image file names by using the count of the number of images on the SD card
	char file_jpg[30];
		
	sprintf(file_jpg, "%s/%d.jpg", PHOTO_DIRECTORY, numFiles+1);
	//sprintf(file_jpg, "Media/Photos/%d.jpg", numFiles+1);
	
	char file_bmp[30];
	sprintf(file_bmp, "%s/%d.bmp", PHOTO_ICONDIRECTORY, numFiles+1);
	
	//
	// Save the image as a JPEG
	//
		
	FIL file;
	if(!SDCard_OpenFile(&file, file_jpg, FA_WRITE | FA_CREATE_NEW))
	{
		while(1){}
	}
		
	jpeg_write(&file, (uint8_t *)Camera_BufferAddress(), 480, 272);

	// Close the file
	SDCard_CloseFile(&file);
		
	//
	// Save a 48x48 bmp version of the image
	//
		
	if(!SDCard_OpenFile(&file, file_bmp, FA_WRITE | FA_CREATE_NEW))
	{
		while(1){}
	}
		
	// Write buffer to bmp
	bmp_write(&file, (uint8_t *)Camera_BufferAddress(), 480, 272, 48, 48);
		
	// Close the file
	SDCard_CloseFile(&file);
}