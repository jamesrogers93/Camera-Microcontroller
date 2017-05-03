#include "Camera.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Touch
#include "Touch_Handler.h"

// Button
#include "Button_Handler.h"

// SDCard
#include "sdcard_module.h"

// Camera
#include "camera_module.h"

// Camera application
#include "Camera_Globals.h"
#include "Camera_View.h"
#include "Camera_Photos.h"

// RTOS
#include "cmsis_os.h"

extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

int RUN = 1;
int SDCardPrompted = 0;
enum CAMERA_STATE Camera_State = CAMERA_VIEW;

void Camera_PromptSDCard(void);

void Camera_runThread(void const *arg);
osThreadDef(Camera_runThread, osPriorityNormal, 1, 0);

void CameraApp_initalise(void)
{
	Camera_View_Initalise();
	Camera_Photos_Initalise();
}

void Camera_run(void)
{
	Camera_runThread(0);
	//osThreadId id1;
	//id1 = osThreadCreate(osThread(Camera_runThread), NULL);
	//if(id1 == NULL)
	//{
		 //Failed to create thread
	//}
}

void Camera_runThread(void const *arg)
{
	while(RUN)
	{
		// Check if the SDCard is inserted
		if(SDCard_IsDetected())
		{
			// An SDCard is inserted.
			
			// Check if we just prompted the user to insert the SDCard
			// I.E. The card has just been inserted, now we need to prepare
			// for the camera states and reconfigure the SDCard.
			if(SDCardPrompted)
			{
				// Clear the screen for camera
				GLCD_ClearScreen();
				
				// Release the SDCardPrompted flag
				SDCardPrompted = 0;
				
				// Reset the SDCard
				SDCard_Initalise();
				
				Camera_State = CAMERA_PHOTOS;
			}

			// Now go into the cameras current state
			switch(Camera_State)
			{
				// Go to the camera view state.
				case CAMERA_VIEW:
					Camera_State = Camera_View_Run();
					break;
					
				// Go to the camera photos state
				case CAMERA_PHOTOS:
					Camera_State = Camera_Photos_Run();
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
			// No SDCard is inserted.
			
			// If we have already prompted the user to insert the SDCard,
			// there is no need to draw the prompt to screen again
			if(!SDCardPrompted)
			{	
				// Stop the Camera
				Camera_Pause();
				
				// Clear the screen
				GLCD_ClearScreen(); 
				
				// Prompt the user to insert the SDCard
				Camera_PromptSDCard();				
				
				// Indicate that the user has been prompted to insert the SDCard
				SDCardPrompted = 1;
				
				// Enable the app to draw to screen once the SDCard is inserted
				Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
			}
		}
		
		// Update the input handlers
		Touch_Handler_Update();
		Button_Handler_Update();
		
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
