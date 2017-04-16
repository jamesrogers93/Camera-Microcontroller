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

#include "stm32746g_discovery.h"

// STD
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// FatFs
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"


void SDCard_Config(void);
int SDCard_IsDetected(void);
int SDCard_OpenFile(FIL *file, const char *filePath, uint8_t mode);
int SDCard_CloseFile(FIL *file);

int SDCard_GetBMPFileName(const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex);
int SDCard_GetNumFileType(const char* DirName, const char* FileType, const uint8_t FileTypeLen);
	

#endif /* _SDCARD_MODULE_H */

