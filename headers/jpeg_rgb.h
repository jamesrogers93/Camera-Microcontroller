/**
  ******************************************************************************
  * @file    jpeg_rgb.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    05-05-2017
  * @brief   A data structure to hold RGB components.
	*
  ******************************************************************************
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __JPEG_RGB_H
#define __JPEG_RGB_H

/** @addtogroup JPEG_MODULE
  * @{
  */

/** @defgroup JPEG_RGB
  * @{
  */
	
/** @defgroup JPEG_RGB_Public_Types
  * @{
  */
	
/**
  * @brief  Contains the RGB components for a pixel.
  */
typedef struct RGB
{
  uint8_t B;
  uint8_t G;
  uint8_t R;
}RGB_typedef;

/**
  * @}
  */ 
	
/**
  * @}
  */ 

/**
  * @}
  */ 

#endif /* __JPEG_RGB_H */
