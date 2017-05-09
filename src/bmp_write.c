/**
  ******************************************************************************
  * @file    bmp_write.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An implementation to write a bmp image to a file.
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "bmp_write.h"
#include "bmp_fileheader.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/** @addtogroup BMP_MODULE
  * @{
  */

/** @defgroup BMP_WRITE
  * @{
  */
	
/** @defgroup BMP_WRITE_Public
  * @{
  */
	
/**
  * @brief  Writes a bmp image to a FIL.
	* @param	file: A pointer to a FIL object
	* @param	buffer: Pointer to an image buffer
	* @param  img_width: width of the image
	* @param  img_height: height of the image
	* @param  target_width: target width of the image to be written
	* @param  target_height: target height of the image to be written
  * @retval status: The status of the bmp reader
  */
uint8_t bmp_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height, uint16_t target_width, uint16_t target_height)
{
	uint8_t status = BMPWRITE_ERROR;
	BitMap bitMapHeader;
	
	// Fill header
	bitMapHeader.Signature = 0x4D42;
	bitMapHeader.Reserved1 = 0x0000128A;
	bitMapHeader.Reserved2 = 0x00000000;
	bitMapHeader.DataOffSet = 0x0000008A;
	
	bitMapHeader.Size = 0x0000007C;
	bitMapHeader.Width = 0x00000030;
	bitMapHeader.Height = 0x00000030;
	bitMapHeader.Planes = 0x0001;
	bitMapHeader.BitsPerPixel = 0x0010;
	bitMapHeader.Compression = 0x00000003;
	bitMapHeader.SizeImage = 0x00001200;
	bitMapHeader.XPixelsPreMeter = 0x00000B13;
	bitMapHeader.YPixelsPreMeter = 0x00000B13;
	bitMapHeader.ColorsUsed = 0x00000000;
	bitMapHeader.ColorsImportant = 0x00000000;
	
	// image is 480 x 272.
	// we want to resize it to 48x48 without warping it.
	// sample from the center of the image or dims 272x272.
	// for easy conversion to 48x48, we are instead going to sample from 240x240 as 48 is a multiple.
	uint16_t resampleSize = 240;
	uint16_t width = 480;
	uint16_t height = 272;
	
	uint16_t discardRows = ((height - resampleSize) * 0.5);
	uint16_t discardColumns = ((width - resampleSize) * 0.5);
	
	// Resize image to 240x240
	
	// Get pointer to the begining of the image
	uint16_t *pixel_resize = (uint16_t *)buffer;
	
	// Get pointer to the begining of the image we want to sample
	uint16_t *pixel_sample = (uint16_t *)buffer + ((width * discardRows) + discardColumns);
	uint32_t counter = 0;
	
	int i;
	for(i = 0; i < 240; i++)
	{
		int j;
		for(j = 0; j < 240; j++)
		{
			*pixel_resize = *pixel_sample;
			
			pixel_resize++;
			pixel_sample++;
		}
		
		// Move pixel to starting point of next row.
		// x2 because discard columns is only the amount of columns to be removed on one side.
		pixel_sample += (discardColumns*2);
	}
	
	// Now scale image down to 48x48
	
	// The new pixels array with the resized image.
	uint16_t pixels[48 * 48] = {0};
	
	// Move pointer to the begining of the part where we want to sample
	pixel_sample = (uint16_t *)buffer + ((resampleSize * 2) + 2);
	
	// Neighbouring pixel indexes
	int pixelIndex[25] = {(-resampleSize*2)-2, (-resampleSize*2)-1, (-resampleSize*2), (-resampleSize*2)+1, (-resampleSize*2)+2,
														(-resampleSize)-2, 	 (-resampleSize)-1,   (-resampleSize),   (-resampleSize)+1,   (-resampleSize)+2,
														 -2, 							 	  -1, 								  0, 							   1, 								  2,
														(resampleSize)-2, 	 (resampleSize)-1,   	 (resampleSize),    (resampleSize)+1,    (resampleSize)+2,
													  (resampleSize*2)-2,  (resampleSize*2)-1,   (resampleSize*2),  (resampleSize*2)+1,  (resampleSize*2)+2};
	
	// RGB masks for conversion
	uint16_t red_mask = 0xF800;
	uint16_t green_mask = 0x7E0;
	uint16_t blue_mask = 0x1F;
	
	for(i = 0; i < 48; i++)
	{
		int j;
		for(j = 0; j < 48; j++)
		{
			// Sample neighbouring pixels
			
			// The RGB values that will be accumulated
			uint16_t R = 0, G = 0, B = 0;
			
			// The pixel from the image buffer
			uint16_t pix = 0;
			
			int k;
			for(k = 0; k < 25; k++)
			{
				// Get a neighnouring pixel from the image buffer
				int neighbour = pixelIndex[k];
				pix = *(pixel_sample + neighbour);
				
				// Convert RGB16 to RGB888
				uint8_t R5 = (pix & red_mask) >> 11;
				uint8_t G6 = (pix & green_mask) >> 5;
				uint8_t B5 = (pix & blue_mask);		

				uint8_t R8 = ( R5 * 527 + 23 ) >> 6;
				uint8_t G8 = ( G6 * 259 + 33 ) >> 6;
				uint8_t B8 = ( B5 * 527 + 23 ) >> 6;
				
				// Accumulate RGB
				R += (uint16_t)R8;
				G += (uint16_t)G8;
				B += (uint16_t)B8;
			}
			
			// Divide by 25 for average.
			//float i9 = 1/9;
			R /= 25;
			G /= 25;
			B /= 25;
			
			// Convert RGB88 back to RGB16
			uint8_t R5 = R  >> 3;  // 5-bit red
			uint8_t G6 = G  >> 2;  // 6-bit green
			uint8_t B5 = B  >> 3;  // 5-bit blue
			uint16_t colour16 = (uint16_t) B5 + (G6<<5) + (R5<<(5+6));
			
			// Place new pixel in new image
			pixels[counter] = colour16;
			
			// Increment pixel index
			counter++;
			
			//Increment pixel sample pointer to correct column
			pixel_sample += 5;
		}
		
		//Increment pixel sample pointer to correct row
		pixel_sample += (resampleSize*4);
	}
	
	// Write the header to file
	uint32_t BytesRead = 0;
	if(f_write(file, &bitMapHeader, sizeof(bitMapHeader), &BytesRead) != FR_OK)
	{
		return status;
	}
	
	// Move file pointer to bmp pixel data
	if(f_lseek(file, bitMapHeader.DataOffSet) != FR_OK)
	{
		return status;
	}
	
	// Write bitmap to bmp file
	if(f_write(file, &pixels, bitMapHeader.Width * bitMapHeader.Height * 2, &BytesRead) != FR_OK)
	{
		return status;
	}
	
	status = BMPWRITE_OK;
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
