/**
  ******************************************************************************
  * @file    bmp_fileheader.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   A data structure to contain the header of a bitmap file
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BMP_FILEHEADER_H
#define _BMP_FILEHEADER_H

/** @addtogroup BMP_MODULE
  * @{
  */

/** @defgroup BMP_FILEHEADER
  * @{
	*
	* A data structure to contain the header of a bitmap file
  */
	
/** @defgroup BMP_FILEHEADER_Public
  * @{
  */
	
#pragma pack(push, 1)
	
/**
  * @brief  Contains the bitmap header components for a bmp file.
  */
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

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */

#endif /* _BMP_FILEHEADER_H */
