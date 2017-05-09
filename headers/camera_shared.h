/**
  ******************************************************************************
  * @file    camera_shared.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   This file holds shared resources for the states in the camera state machine.
	* 
  ******************************************************************************
	*/
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_SHARED_H
#define _CAMERA_SHARED_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_SHARED
  * @{
		*
	* This module contains all of the shared resources for the states in the state machine.
  */
	
#define CAMERA_OK				((uint8_t)0x00)
#define CAMERA_ERROR		((uint8_t)0x01)

#define CAMERA_DRAWON 	((uint8_t)0x00)
#define CAMERA_DRAWOFF 	((uint8_t)0x01)

/**
  * @brief	The state function pointer which points the the state to be executed next.
	*
	* This is set to the camera_cameraview_run() as default in camera_run(). 
	* This function pointer is modified by the states when a state transition occurs.
  */
extern uint8_t(*camera_state_ptr)(void);

extern uint8_t Camera_DrawToScreen;

/**
  * @brief	Provides access to the image buffer address.
	*	@retval address: The address of the image buffer
  */
uint32_t ImageBufferAddress(void);

/**
  * @}
  */
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* _CAMERA_SHARED_H */
