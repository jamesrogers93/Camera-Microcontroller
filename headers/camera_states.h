/**
  ******************************************************************************
  * @file    camera_states.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   This file holds the function protypes of the states used in the camera state machine.
	* 
  ******************************************************************************
	*/
		
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_STATES_H
#define _CAMERA_STATES_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
	*
	* This module contains all of the state machine related functionality.
	* States are modified by changing the function pointer, camera_state_ptr in camera_shared.c, a file
	* with shared resources for all states to access.
  */
	
/** @defgroup CAMERA_STATES_CAMERAVIEW
  * @{
	*
	* This module contains all of the cameraview state related functionality. Specifically, this
	* module will handle displaying the camera view to the screen.
  */
	
/** @defgroup CAMERA_STATES_CAMERAVIEW_Public
  * @{
	*
	* The public functions and variables
  */
	
/**
  * @brief  Displays the camera to the screen.
  * @retval status: The status of the camera
	*
	* Here the output from the camera is displayed fullscreen.
	* This state will set the state to camera_takepicture_run() if the button is pressed.
	* This state will set the state to camera_photopreviews_run() if the screen is touched. 
  */
uint8_t camera_cameraview_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/** @defgroup CAMERA_STATES_PHOTOPREVIEWS
  * @{
	*
	* This module contains all of the photopreview state related functionality. Specifically, this
	* module will handle displaying photo previews to the screen.
  */
	
/** @defgroup CAMERA_STATES_PHOTOPREVIEWS_Public
  * @{
  */
	
/**
  * @brief  Displays the photo preview icons from the SD card to the screen.
  * @retval status: The status of the camera
  *
	* Here the state will load the BMP preview icons from the SD card and display them to the screen.
	* This state will set the state function pointer to the camera_photospecific_run() state if an image is touched to display a 
	* fullscreen version of it. For camera_photospecific_run() to know which image to display, the photoSpecificID in camera_shared.c is set to the id of the image touched.
	* This state will set the state to camera_cameraview_run() if the camera icon is touched.
	* This state will also set the state function pointer to the camera_sdprompt_run() state if there is no SD card detected.
	*/
uint8_t camera_photopreviews_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/** @defgroup CAMERA_STATES_PHOTOSPECIFIC
  * @{
	*
	* This module contains all of the photospecific state related functionality. Specifically, this
	* module will handle displaying a full size photo to the screen.
  */
	
/** @defgroup CAMERA_STATES_PHOTOSPECIFIC_Public
  * @{
  */
	
/**
  * @brief  Displays the a fullscreen JPEG photo.
  * @retval status: The status of the camera
	*
	* Here the state will load the JPEG image specified by photoSpecificID in camera_shared.c.
	* This state will change the state to the camera_photopreviews_run() state if the screen is touched.
	* This state will also set the state function pointer to the camera_sdprompt_run() state if there is no SD card detected.
  */
uint8_t camera_photospecific_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/** @defgroup CAMERA_STATES_SDPROMPT
  * @{
	*
	* This module contains all of the sdprompt state related functionality.  Specifically, this
	* module will handle prompting the sd card and reinitalise it once detected.
  */
	
/** @defgroup CAMERA_STATES_SDPROMPT_Public
  * @{
  */
	
/**
  * @brief  Prompts the user to insert the SD card.
  * @retval status: The status of the camera
	*
	* This state will prompt the user to enter an SD card if it is not detected. Once the SD card is detected, it will be 
	* reinitalised and the state will be returned to the camera_cameraview_run() state as default.
  */
uint8_t camera_sdprompt_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/** @defgroup CAMERA_STATES_TAKEPICTURE
  * @{
	*
	* This module contains all of the takepicture state related functionality.  Specifically, this
	* module will handle taking a picture and storing it on the SD card.
  */
	
/** @defgroup CAMERA_STATES_TAKEPICTURE_Public
  * @{
  */
	
/**
  * @brief  Takes a picture.
  * @retval status: The status of the camera
	*
	* This state will take a picture by storing a snapshot of the camera buffer to a BMP preview icon and a full size JPEG
	* icon to the SD card.
	* This state will transition to the camera_sdprompt_run() state if the SD card is not detected.
  */
uint8_t camera_takepicture_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* _CAMERA_STATES_H */
