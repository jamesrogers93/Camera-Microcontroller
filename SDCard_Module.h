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

// LibJpeg
#include "decode.h"

#pragma pack(push, 1)
typedef struct BitMap
{
    short Signature;
    long Reserved1;
    long Reserved2;
    long DataOffSet;

    long Size;
    long Width;
    long Height;
    short Planes;
    short BitsPerPixel;
    long Compression;
    long SizeImage;
    long XPixelsPreMeter;
    long YPixelsPreMeter;
    long ColorsUsed;
    long ColorsImportant;
    unsigned char *pixel_data;
}BitMap;
#pragma pack(pop)

typedef struct RGB
{
  uint8_t B;
  uint8_t G;
  uint8_t R;
}RGB_typedef;

void SDCard_Config(void);

int SDCard_IsDetected(void);

int SDCard_loadBMP(unsigned char *buffer, const char* filePath);
int SDCard_GetBMPFileName(const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex);
int SDCard_loadJPEG(unsigned char *buff, const char* filePath, uint16_t *imgWidth,uint16_t *imgHeight);
	

#endif /* _SDCARD_MODULE_H */

