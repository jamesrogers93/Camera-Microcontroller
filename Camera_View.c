#include "Camera_View.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_Touch.h"
#include "Camera_Defines.h"
#include "Icon_Browse.c"
#include "Data_Types.h"
#include "Touch_Handler.h"

extern GLCD_FONT     GLCD_Font_16x24;

Entity Camera_ViewEntities[1];
unsigned int num_entities;

void Camera_View_Initalise(void)
{
	//Camera_ViewEntities[0] = Entity_Make(Point_2D_Make(50,50), Icon_Make(Icon_Browse.width, Icon_Browse.height, Icon_Browse.bytes_per_pixel, Icon_Browse.pixel_data));
	Camera_ViewEntities[0] = Entity_Make(
																				Point_2D_Make(
																											GLCD_CAMERA_WIDTH-Icon_Browse.width - GLCD_CAMERA_EDGE_PADDING, 
																											GLCD_CAMERA_HEIGHT-Icon_Browse.height - GLCD_CAMERA_EDGE_PADDING), 
																				&Icon_Browse);
	num_entities = 1;
	
}

void Camera_StateView(void)
{
	// Draw the state string to the screen
	GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
	GLCD_SetFont (&GLCD_Font_16x24);
	GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "View State");
	
	// Draw the browse icon to the screen
		GLCD_DrawBitmap( 
									Camera_ViewEntities[0].position.x, 
									Camera_ViewEntities[0].position.y, 
									Camera_ViewEntities[0].image->width,
									Camera_ViewEntities[0].image->height, 
									Camera_ViewEntities[0].image->pixel_data);
	
	// Check if the browse icon has been pressed
	TOUCH_STATE  tsc_state;
  Touch_GetState (&tsc_state); /* Get touch state */   
  if (tsc_state.pressed) {
    
		Point_2D point = {tsc_state.x, tsc_state.y};
		
		if(Point_Entity_Collision(&point, Camera_ViewEntities, num_entities))
		{
			
		}
  }
}
