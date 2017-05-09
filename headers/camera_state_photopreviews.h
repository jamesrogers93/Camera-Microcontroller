/**
  ******************************************************************************
  * @file    camera_state_photopreviews.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Contains the initaliser for the camera_photopreviews_run() state.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_STATE_PHOTOPREVIEWS_H
#define _CAMERA_STATE_PHOTOPREVIEWS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup CAMERA_APPLICATION
  * @{
  */
	
/** @defgroup CAMERA_STATES
  * @{
  */
	
/** @defgroup CAMERA_STATES_Public
  * @{
  */
	
/**
  * @brief  Initalises the camera_photopreviews_run() state.
  * @retval status: The status of the camera
  */
uint8_t camera_photopreviews_initalise(void);

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

#endif /* _CAMERA_STATE_PHOTOPREVIEWS_H */
