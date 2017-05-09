/**
  ******************************************************************************
  * @file    touch_handler.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-March-2017
  * @brief   An implementation to check if the screen was touched and where it was touched.
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "Touch_Handler.h"
#include "Board_Touch.h"
#include "stm32f7xx_hal.h"

/** @addtogroup INPUT_MODULE
  * @{
  */
	
/** @addtogroup TOUCH_HANDLER
  * @{
	* Handles screen touch.
  */
	
/** @addtogroup TOUCH_HANDLER_Public
  * @{
  */
	
/**
  * @brief  Checks if the screen was touched and provides touch coordinates.
	* @param	x: A pointer to the x touch coordinate. 
	* @param	y: A pointer to the y touch coordinate. 
  * @retval status: The status of the screen touch
  */
uint8_t TouchHandler_touchPosition(int *x, int *y)
{
	// Check if the display was touched
	TOUCH_STATE  tsc_state;
	Touch_GetState (&tsc_state); /* Get touch state */ 

	HAL_Delay(100);
  
	if (tsc_state.pressed) 
	{
		// Get the position of the touch and store it in the parameter, position
		*(x) = tsc_state.x;
		*(y) = tsc_state.y;
			
		return TOUCHSCREEN_TOUCHED;
	}
	
	return TOUCHSCREEN_NOT_TOUCHED;
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
