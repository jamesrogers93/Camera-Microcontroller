
#include "camera_main.h"
#include "camera_shared.h"
#include "camera_states.h"

#include "camera_state_photopreviews.h"

#include "touch_handler.h"

uint8_t status;


void camera_stateMachine(void)
{
	// Run the state machine until ->
		// The state function pointer is null. OR
		// The state machine has finished. OR
		// An error has occured.
	while(camera_state_ptr != 0 && camera_state_ptr() == CAMERA_OK);
}

uint8_t camera_run(void)
{
	
	uint8_t status = CAMERA_ERROR;
	
	// Initalise camera
	if(camera_photopreviews_initalise() != CAMERA_OK)
	{
		return status;
	}
	
	// Set the first state in the statemachone
	camera_state_ptr = &camera_cameraview_run;
	
	// Run camera state machine
	camera_stateMachine();
	
	return status;
}
