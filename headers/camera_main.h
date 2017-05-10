/**
  ******************************************************************************
  * @file    camera_main.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Handles the camera application
  ******************************************************************************
  */
		
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_MAIN_H
#define _CAMERA_MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup CAMERA_APPLICATION
  * @{
	* 
	* The camera_run() function in the camera_main.h file is the entry point to the camera 
	* application. This function is responsible for initialising the camera and executing the 
	* state machine. The method will only return control to the calling function if the camera 
	* has completed it's execution, or an error has occurred during initialisation or the 
	* execution of the state machine.
  */
	
/** @defgroup CAMERA_MAIN
  * @{
  */
	
/** @defgroup CAMERA_MAIN_Public
  * @{
  */
	
/**
  * @brief  The main entry point to start the camera application.
  * @retval status: The status of the camera
  */
uint8_t camera_run(void);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* _CAMERA_MAIN_H */
