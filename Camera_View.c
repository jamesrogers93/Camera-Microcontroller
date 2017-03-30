#include "Camera_View.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Touch
#include "Touch_Handler.h"

// Camera application
#include "Camera_Defines.h"
#include "Camera_Globals.h"
#include "Icons/Icon_Photos.c"

extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

Entity Camera_ViewEntities[1];
unsigned int num_viewEntities;


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
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Camera State");
		
		// Draw the photos icon to the screen.
		GLCD_DrawBitmap( 
										Camera_ViewEntities[0].position.x, 
										Camera_ViewEntities[0].position.y, 
										Camera_ViewEntities[0].image->width,
										Camera_ViewEntities[0].image->height, 
										Camera_ViewEntities[0].image->pixel_data);
	}
	
	// Check if the photos icon has been pressed.
	Point_2D point;
	if(Screen_Touched(&point))
	{
		// Check if the touch position collides with the entities.
		if(Point_Entity_Collision(&point, Camera_ViewEntities, num_viewEntities) != 0)
		{
			GLCD_ClearScreen();
			
			// Release the draw to screen flag, enabling items to be drawn again.
			Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
			
			// Return the next state.
			return CAMERA_PHOTOS;
		}
	}
	
	// Remain in the same state/
	return CAMERA_VIEW;
}
