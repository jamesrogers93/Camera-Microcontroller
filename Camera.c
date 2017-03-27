#include "Camera.h"

#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Touch.h"
#include "Camera_Defines.h"
#include "SDCard_Module.h"
#include "Camera_View.h"
#include "Camera_Browse.h"

extern GLCD_FONT     GLCD_Font_16x24;

int RUN = 1;
int SDCardPrompted = 0;
enum CAMERA_STATE Camera_State = CAMERA_VIEW;

void Camera_initalise(void)
{
	Camera_View_Initalise();
	Camera_Browse_Initalise();
}

void Camera_run(void)
{
	while(RUN)
	{
		if(SDCard_IsDetected())
		{
			// Check if we just prompted the user to insert the SDCard
			if(SDCardPrompted)
			{
				// Clear the screen for camera
				GLCD_ClearScreen();
				
				// Release the SDCardPrompted flag
				SDCardPrompted = 0;
			}

			// Now go into the cameras current state
			switch(Camera_State)
			{
				// Go to the camera view state.
				case CAMERA_VIEW:
					Camera_StateView();
					break;
					
				// Go to the camera browse state
				case CAMERA_BROWSE:
					//Camera_StateBrowse();
					break;
				
				// No state has been defined. Display message and terminate
				default:
					GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
					GLCD_SetFont (&GLCD_Font_16x24);
					GLCD_DrawString(100, 100, "ERROR: State not specified");
					RUN = 0;
					break;
			}	
		}
		else
		{
			// If we have already prompted the user to insert the SDCard,
			// there is no need to draw the prompt to screen again
			if(!SDCardPrompted)
			{	
				// Clear the screen
				GLCD_ClearScreen(); 
				
				// Prompt the user to insert the SDCard
				Camera_PromptSDCard();				
				
				// Indicate that the user has been prompted to insert the SDCard
				SDCardPrompted = 1;
			}
		}
	}
}

void Camera_PromptSDCard(void)
{
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_WIDTH_HALF - ((CAMERA_SDCARD_PROMPT_MSG_LEN*0.5) * GLCD_CHAR_WIDTH), 
									GLCD_CAMERA_HEIGHT_HALF, 
									CAMERA_SDCARD_PROMPT_MSG);
}
