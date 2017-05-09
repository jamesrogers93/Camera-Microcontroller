/**
  ******************************************************************************
  * @file    bmp_read.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An interface to read a bmp image from a file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BMP_READ_H
#define _BMP_READ_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "ff.h"

/** @addtogroup BMP_MODULE
  * @{
	*
	* Provides an interface to read and write BMP files
  */

/** @defgroup BMP_READ
  * @{
	*
	*	Provides an interface to read BMP files
  */
	
/** @defgroup BMP_READ_Public
  * @{
  */
	
#define BMPREAD_OK		((uint8_t)0x00)
#define BMPREAD_ERROR	((uint8_t)0x01)

/**
  * @brief  Reads a bmp image from a fil.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: pointer to the width of the image
	* @param  img_height: pointer to the height of the image
  * @retval status: The status of the bmp reader
  */
uint8_t bmp_read(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height);

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
#endif /* _BMP_READ_H */
