/**
  ******************************************************************************
  * @file    camera_module.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    03-05-2017
  * @brief   An interface for communicating with a camera connected through DCMI.
	*
  ******************************************************************************
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_MODULE_H
#define _CAMERA_MODULE_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/** @defgroup CAMERA_MODULE
  * @{
  */
	
/** @defgroup CAMERA_MODULE_Public_Defines
  * @{
  */
	
/** @defgroup CAMERA_MODULE_Status
  * @{
  */
	
#define CAMERAMOD_OK		 ((uint8_t)0x00)
#define CAMERAMOD_ERROR  ((uint8_t)0x01)

/**
  * @}
  */ 
	
/**
  * @}
  */ 

/** @defgroup CAMERA_MODULE_Public_Functions
  * @{
  */
	
/**
  * @brief  Initializes the camera.
  * @retval Status: Camera status
  */
uint8_t Camera_Initalise(void);

/**
  * @brief  Resumes the camera stream.
  * @retval None
  */
void Camera_Resume(void);

/**
  * @brief  Pauses the camera stream.
  * @retval None
  */
void Camera_Pause(void);

/**
  * @brief  Starts the camera in continuous mode.
	* @param  buffer: pointer to the camera output buffer
  * @retval None
  */
void Camera_Continuous(uint8_t *buffer);

/**
  * @brief  Captures a snapshot of the camera.
	* @param  buffer: pointer to the camera output buffer
  * @retval None
  */
void Camera_Snapshot(uint16_t *buffer);

/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* _CAMERA_MODULE_H */
