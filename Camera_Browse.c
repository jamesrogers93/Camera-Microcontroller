#include "Camera_Browse.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Touch.h"
#include "Camera_Defines.h"

extern GLCD_FONT     GLCD_Font_16x24;

void Camera_Browse_Initalise(void)
{
	
}

void Camera_StateBrowse(void)
{
	// Draw the state string to the screen
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Browse State");
}
