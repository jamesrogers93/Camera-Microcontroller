/**
  ******************************************************************************
  * @file    camera_main.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Handles the camera application
  ******************************************************************************
  */
		
/* Includes ------------------------------------------------------------------*/
#include "camera_main.h"
#include "camera_shared.h"
#include "camera_states.h"
#include "camera_state_photopreviews.h"
#include "cmsis_os.h"

/** @addtogroup CAMERA_APPLICATION
  * @{
  */
	
/** @addtogroup CAMERA_MAIN
  * @{
  */
	
/** @defgroup CAMERA_MAIN_Private
  * @{
  */
	
/**
  * @brief  Holds the RTOS task ID for the state machine (NOT IN USE).
  */
osThreadId tid_taskA; 

/**
  * @brief  The status of the camera.
  */
uint8_t status;

	
/**
  * @brief  Runs the camera state machine.
  * @retval None:
  */
void camera_stateMachine(void const *argument);


/**
  * @brief  Defines the statemachine macro for RTOS tasks.
  */
osThreadDef(camera_stateMachine, osPriorityNormal, 1, 0);

	
/**
  * @brief  Runs the camera state machine.
  * @retval None:
  */
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

/**
  * @}
  */ 

/** @addtogroup CAMERA_MAIN_Public
  * @{
  */

/**
  * @brief  The main entry point to start the camera application.
  * @retval status: The status of the camera
  */
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

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 
