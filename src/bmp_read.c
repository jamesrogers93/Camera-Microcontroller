/**
  ******************************************************************************
  * @file    bmp_read.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An implementation to read a bmp image from a file.
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "bmp_read.h"
#include "bmp_fileHeader.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/** @addtogroup BMP_MODULE
  * @{
  */

/** @defgroup BMP_READ
  * @{
  */
	
/** @defgroup BMP_READ_Private
  * @{
  */

/**
  * @brief Used to read 512 byte chunks from a file at a time.
  */
uint8_t sector[512];

/**
  * @brief Indicates the number of bytes read from the a file
  */
uint32_t BytesRead = 0;

/**
  * @}
  */ 
	
/** @defgroup BMP_READ_Public
  * @{
  */

/**
  * @brief  Reads a bmp image from a fil.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: pointer to the width of the image
	* @param  img_height: pointer to the height of the image
  * @retval status: The status of the bmp reader
  */
uint8_t bmp_read(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height)
{
	uint8_t status = BMPREAD_ERROR;
	BitMap bitMapHeader;
	
	// Read bmp header
  if (f_read (file, &bitMapHeader, sizeof(BitMap), (UINT *)&BytesRead) == FR_OK)
	{
		// Check if file loaded is a bitmap
		if(bitMapHeader.Signature != 0x4D42)
		{
			return status;
		}
	}
	
	// Store image dimensions
	*(img_width) = (uint16_t)bitMapHeader.Width;
	*(img_height) = (uint16_t)bitMapHeader.Height;
	
	// Move file pointer to bmp pixel data
	if(f_lseek(file, bitMapHeader.DataOffSet) == FR_OK)
	{
			
		// Load the bmp image buffer in 512 byte chunks
		uint32_t size = bitMapHeader.SizeImage, i1 = 0, index = 0;
		do
		{
			if (size < 512)
			{
				i1 = size;
			}
			else
			{
				i1 = 512;
			}
				
			size -= i1;
			f_read (file, sector, i1, (UINT *)&BytesRead);
			uint32_t BmpAddress = (uint32_t)sector;
				
			for (index = 0; index < i1; index++)
			{
				*(__IO uint8_t*) (buffer) = *(__IO uint8_t *)BmpAddress;
					
				BmpAddress++;  
				buffer++;
			}  
		}
		while (size > 0);
			
		status = BMPREAD_OK;

	}
	
	return status;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
	
/**
  * @}
  */ 
