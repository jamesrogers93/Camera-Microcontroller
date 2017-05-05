/**
  ******************************************************************************
  * @file    bmp_write.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An interface to write a bmp image to a file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BMP_WRITE_H
#define _BMP_WRITE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "ff.h"

/** @addtogroup BMP_MODULE
  * @{
  */

/** @defgroup BMP_WRITE
  * @{
  */
	
/** @defgroup BMP_WRITE_Public_Defines
  * @{
  */
	
/** @defgroup BMP_WRITE_Status
  * @{
  */
	
#define BMPWRITE_OK			((uint8_t)0x00)
#define BMPWRITE_ERROR	((uint8_t)0x01)

/**
  * @}
  */ 
	
/**
  * @}
  */
	
/** @defgroup BMP_WRITE_Public_Functions
  * @{
  */

/**
  * @brief  Writes a bmp image to a FIL.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: width of the image
	* @param  img_height: height of the image
	* @param  target_width: target width of the image to be written
	* @param  target_height: target height of the image to be written
  * @retval status: The status of the bmp reader
  */
uint8_t bmp_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height, uint16_t target_width, uint16_t target_height);

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
#endif /* _BMP_WRITE_H */
