
#include "camera_main.h"
#include "camera_shared.h"
#include "camera_states.h"

#include "camera_state_photopreviews.h"

#include "touch_handler.h"
#include "button_handler.h"

uint8_t camera_run(void)
{
	
	uint8_t status = CAMERA_ERROR;
	
	// Initalise camera
	if(camera_photopreviews_initalise() != CAMERA_OK)
	{
		return CAMERA_ERROR;
	}
	
	camera_state_ptr = &camera_cameraview_run;
	//camera_state_ptr = &camera_photopreviews_run;
	
	// Run state machine
	while(camera_state_ptr != 0 && camera_state_ptr() == CAMERA_OK)
	{
		Touch_Handler_Update();
		Button_Handler_Update();
	}
	
	return status;
}
