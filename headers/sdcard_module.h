/**
  ******************************************************************************
  * @file    SDCard.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   This file provides functions for the SDCard
  ******************************************************************************
  */
	
#ifndef _SDCARD_MODULE_H
#define _SDCARD_MODULE_H

#include <stdint.h>
#include "ff.h"

#define SDCARD_OK								((uint8_t)0x00)
#define SDCARD_ERROR_INITALISE  ((uint8_t)0x01)
#define SDCARD_ERROR_DRIVER  		((uint8_t)0x02)
#define SDCARD_ERROR_FILE  			((uint8_t)0x03)

uint8_t SDCard_Initalise(void);
uint8_t SDCard_IsDetected(void);
uint8_t SDCard_OpenFile(FIL *file, const char *filePath, uint8_t mode);
uint8_t SDCard_CloseFile(FIL *file);
uint8_t SDCard_GetBMPFileName(uint16_t *numFiles, const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex);
uint8_t SDCard_GetNumFileType(uint16_t *numFiles, const char* DirName, const char* FileType, const uint8_t FileTypeLen);
	

#endif /* _SDCARD_MODULE_H */

