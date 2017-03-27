#include "Camera_Photos.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Camera_Defines.h"
#include "Data_Types.h"
#include "Icons/Icon_Camera.c"
#include "Touch_Handler.h"

extern GLCD_FONT     GLCD_Font_16x24;

Entity Camera_PhotosEntities[1];
unsigned int num_PhotosEntities;

void Camera_Photos_Initalise(void)
{
	Camera_PhotosEntities[0] = Entity_Make(
																				Point_2D_Make(
																											GLCD_CAMERA_WIDTH-Icon_Camera.width - GLCD_CAMERA_EDGE_PADDING, 
																											GLCD_CAMERA_HEIGHT-Icon_Camera.height - GLCD_CAMERA_EDGE_PADDING), 
																				&Icon_Camera);
	num_PhotosEntities = 1;
}

enum CAMERA_STATE Camera_Photos_Run(void)
{
	// Draw the state string to the screen
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Photos State");
	
	// Draw the photos icon to the screen
	GLCD_DrawBitmap( 
									Camera_PhotosEntities[0].position.x, 
									Camera_PhotosEntities[0].position.y, 
									Camera_PhotosEntities[0].image->width,
									Camera_PhotosEntities[0].image->height, 
									Camera_PhotosEntities[0].image->pixel_data);
	
	// Check if the photos icon has been pressed
	Point_2D point;
	if(Screen_Touched(&point))
	{
		if(Point_Entity_Collision(&point, Camera_PhotosEntities, num_PhotosEntities) != 0)
		{
			GLCD_ClearScreen();
			return CAMERA_VIEW;
		}
	}
	
	
	
	return CAMERA_PHOTOS;
}
