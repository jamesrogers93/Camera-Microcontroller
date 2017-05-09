/**
  ******************************************************************************
  * @file    jpeg_write.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    05-05-2017
  * @brief   An interface to write a 16bit rgb image buffer to a jpeg file.
	*
  ******************************************************************************
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __JPEG_WRITE_H
#define __JPEG_WRITE_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"

/** @addtogroup JPEG_MODULE
  * @{
  */
	
/** @defgroup JPEG_WRITE
  * @{
	*
	* An interface to write an image buffer to a JPEG file.
  */
	
/** @defgroup JPEG_WRITE_Public
  * @{
  */
	
#define JPGWRITE_OK			((uint8_t)0x00)
#define JPGWRITE_ERROR	((uint8_t)0x01)

/**
  * @brief  Writes a jpeg image to a FIL.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: width of the image
	* @param  img_height: height of the image
  * @retval None
  */
void jpeg_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height);

/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
/**
  * @}
  */ 
	
#endif /* __JPEG_DECODE_H */
