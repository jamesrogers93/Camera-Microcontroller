#include "camera_states.h"
#include "camera_shared.h"
#include "sdcard_module.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Message defines
#define PROMPT_MSG "INSERT SDCARD"
#define PROMPT_MSG_LEN 13
#define CHAR_WIDTH 16

extern GLCD_FONT     GLCD_Font_16x24;

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
