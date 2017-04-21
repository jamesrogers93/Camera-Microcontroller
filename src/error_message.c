#include "Error_Message.h"

//#include <stdio.h>
#include <string.h>
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Camera_Globals.h"

extern GLCD_FONT     GLCD_Font_16x24;
void Error_DisplayMessage(const char *message)
{
	const size_t messLenHalf = strlen(message) * 0.5;
	GLCD_ClearScreen();
	GLCD_SetForegroundColor(GLCD_COLOR_RED);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_WIDTH_HALF - (messLenHalf * GLCD_CHAR_WIDTH), 
									GLCD_CAMERA_HEIGHT_HALF, 
									message);
		
	while(1)
	{
	}
}
