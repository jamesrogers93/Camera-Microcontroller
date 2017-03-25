#include "Camera.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Camera_Module.h"
#include "SDCard_Module.h"

extern GLCD_FONT     GLCD_Font_16x24;

void Camera_initalise(void)
{
	
}

void Camera_run(void)
{
	while(!SDCard_IsDetected())
	{
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(100,100,"Please insert SDCard");
		
	}
	
	// Erase font
	GLCD_ClearScreen();
	
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(100,100,"SDCard Inserted");
}
