/**
  ******************************************************************************
  * @file    touch_handler.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-March-2017
  * @brief   An interface to check if the screen was touched and where it was touched.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TOUCH_HANDLER_H
#define _TOUCH_HANDLER_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @defgroup INPUT_MODULE
  * @{
  */
	
/** @defgroup TOUCH_HANDLER
  * @{
  */
	
/** @defgroup TOUCH_HANDLER_Public
  * @{
  */
	
#define TOUCHSCREEN_NOT_TOUCHED	((uint8_t)0x00)
#define TOUCHSCREEN_TOUCHED			((uint8_t)0x01)

	
/**
  * @brief  Checks if the screen was touched and provides touch coordinates.
	* @param	x: A pointer to the x touch coordinate. 
	* @param	y: A pointer to the y touch coordinate. 
  * @retval status: The status of the screen touch
  */
uint8_t TouchHandler_touchPosition(int *x, int *y);

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* _TOUCH_HANDLER_H */
