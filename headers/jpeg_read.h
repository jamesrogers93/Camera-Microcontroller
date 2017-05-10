/**
  ******************************************************************************
  * @file    jpeg_read.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An interface to read a jpeg image from a file.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __JPEG_READ_H
#define __JPEG_READ_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"

/** @addtogroup JPEG_MODULE
  * @{
	*
	* This module allows JPEG images to be read and written to and from a FatFs FIL file.
  */

/** @defgroup JPEG_READ
  * @{
	*
	*	Provides an interface to read JPEG files
  */
	
/** @defgroup JPEG_READ_Public
  * @{
  */
	
#define JPGREAD_OK		((uint8_t)0x00)
#define JPGREAD_ERROR	((uint8_t)0x01)


/**
  * @brief  Reads a jpeg image from a fil.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: pointer to the width of the image
	* @param  img_height: pointer to the height of the image
  * @retval None
  */
void jpeg_read(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height);

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 

#endif /* __JPEG_READ_H */
