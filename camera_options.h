/**
  ******************************************************************************
  * @file    camera_options.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   Specifies options to modify the camera
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CAMERA_OPTIONS_H
#define _CAMERA_OPTIONS_H

/** @defgroup CAMERA_APPLICATION
  * @{
  */

/** @defgroup CAMERA_OPTIONS
  * @{
	*
	* Specifies options to modify the camera behaviour.
  */
	
/**
  * @brief  Specifies the directory of the JPEG photos.
  */
#define PHOTO_DIRECTORY "Media/Photos"

/**
  * @brief  Specifies the directory of the BMP preview icons.
  */
#define PREVIEW_DIRECTORY "Media/Previews"

/**
  * @brief  Specifies the max length of the directoy name.
  */
#define MAX_DIRECTORYNAME_LENGTH 30

/**
  * @brief  Specifies the max length of the file name.
  */
#define MAX_FILENAME_LENGTH 12

/**
  * @}
  */ 
	
/**
  * @}
  */

#endif /* _CAMERA_OPTIONS_H */
