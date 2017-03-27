#include "Camera_View.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Camera_Defines.h"
#include "Icons/Icon_Photos.c"
#include "Touch_Handler.h"
#include "Camera.h"

extern GLCD_FONT     GLCD_Font_16x24;

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
	// Draw the state string to the screen
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Camera State");
	
	// Draw the photos icon to the screen
		GLCD_DrawBitmap( 
									Camera_ViewEntities[0].position.x, 
									Camera_ViewEntities[0].position.y, 
									Camera_ViewEntities[0].image->width,
									Camera_ViewEntities[0].image->height, 
									Camera_ViewEntities[0].image->pixel_data);
	
	// Check if the photos icon has been pressed
	Point_2D point;
	if(Screen_Touched(&point))
	{
		if(Point_Entity_Collision(&point, Camera_ViewEntities, num_viewEntities) != 0)
		{
			GLCD_ClearScreen();
			return CAMERA_PHOTOS;
		}
	}
	
	return CAMERA_VIEW;
}
