/**
  ******************************************************************************
  * @file    sdcard.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An interface for communicating with an SD card.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SDCARD_MODULE_H
#define _SDCARD_MODULE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "ff.h"

/** @defgroup SDCARD_MODULE
  * @{
  */
	
/** @defgroup SDCARD_MODULE_STATUS
  * @{
  */
 
#define SDCARD_OK								((uint8_t)0x00)
#define SDCARD_ERROR_INITALISE  ((uint8_t)0x01)
#define SDCARD_ERROR_DRIVER  		((uint8_t)0x02)
#define SDCARD_ERROR_FILE  			((uint8_t)0x03)

/**
  * @}
  */ 
	
/** @defgroup SDCARD_MODULE_Functions
  * @{
  */

/**
  * @brief  Initializes the SD card.
  * @retval Status: SD card status
  */
uint8_t SDCard_Initalise(void);

/**
  * @brief  Checks if the SD card is detected.
  * @retval Status: SD card status
  */
uint8_t SDCard_IsDetected(void);

/**
  * @brief  Opens a file from the SD card.
	* @param	Fil: A pointer to a file object
	* @param	filePath: The file path to the file
	* @param	mode: The file open mode
  * @retval Status: SD card status
  */
uint8_t SDCard_OpenFile(FIL *file, const char *filePath, uint8_t mode);

/**
  * @brief  Closes a file in the SD card.
	* @param	Fil: A pointer to a file object
  * @retval Status: SD card status
  */
uint8_t SDCard_CloseFile(FIL *file);

/**
  * @brief  Gets BMP file names from the SD card.
	* @param	numFiles: Will equal to the number of bmp files found
	* @param	DirName: The directory path
	* @param	Files: An array which will be filled of bmp file names found
	* @param	maxFiles: The max number of files to be read
	* @param	maxFileName: The max size of the file names
	* @param 	startIndex: The files index to start navigating
  * @retval Status: SD card status
  */
uint8_t SDCard_GetBMPFileName(uint16_t *numFiles, const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex);

/**
  * @brief  Gets BMP file names from the SD card.
	* @param	numFiles: Will equal to the number of bmp files found
	* @param	DirName: The directory path
	* @param	FileType: The file type to be found
	* @param	FileTypeLen: The max length of the files retrieved
  * @retval Status: SD card status
  */
uint8_t SDCard_GetNumFileType(uint16_t *numFiles, const char* DirName, const char* FileType, const uint8_t FileTypeLen);
	
/**
  * @}
  */ 
	
#endif /* _SDCARD_MODULE_H */

