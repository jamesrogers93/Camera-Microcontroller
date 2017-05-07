
#include "camera_main.h"
#include "camera_shared.h"
#include "camera_states.h"
#include "camera_state_photopreviews.h"
#include "cmsis_os.h"
void camera_stateMachine(void const *argument);
osThreadDef(camera_stateMachine, osPriorityNormal, 1, 0);
osThreadId tid_taskA; 

uint8_t status;


void camera_stateMachine(void const *argument)
{

	// Run the state machine until ->
		// The state function pointer is null. OR
		// The state machine has finished. OR
		// An error has occured.
	status = CAMERA_OK;
	while(camera_state_ptr != 0 && status == CAMERA_OK)
	{
		status = camera_state_ptr();
	}
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
	camera_stateMachine(0);

	//tid_taskA = osThreadCreate(osThread(camera_stateMachine), NULL);
	
	for(;;);
	
	return status;
}
