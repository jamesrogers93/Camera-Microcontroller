/**
  ******************************************************************************
  * @file    camera_shared.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   This file holds shared resources for the states in the camera state machine.
	* 
  ******************************************************************************
	*/
	
/* Includes ------------------------------------------------------------------*/
#include "camera_shared.h"
#include "GLCD_Config.h"

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_SHARED
  * @{
  */
	
/**
  * @brief	Draw to screen flag.
	*
	* This is used to prevent drawing the same data to screen multiple times. Once a state draws to the 
	* the screen, it will lock the flag. When the state transitions to a new one, it will release the flag,
	* allowing other states to draw to screen.
  */
uint8_t Camera_DrawToScreen = CAMERA_DRAWON;

/**
  * @brief	Stores the id of an image.
	*
	* This is used to allow the camera_photopreviews_run() state to specify which image has been touched for the
	* camera_photospecific_run() state.
  */
uint32_t photoSpecificID = 0;


/**
  * @brief	Image buffer.
	*
	* This image buffer is initalised to hold all of the pixels on the screen. This buffer is the main container of all 
	* image related computation.
  */
static uint16_t image_buffer[GLCD_WIDTH*GLCD_HEIGHT] __attribute__((at(0xC0260000)));

/**
  * @brief	Provides access to the image buffer address.
	*	@retval address: The address of the image buffer
  */
uint32_t ImageBufferAddress(void)
{
	return ((uint32_t)image_buffer);
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
