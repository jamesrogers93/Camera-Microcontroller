/**
  ******************************************************************************
  * @file    jpeg_write.c 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    05-05-2017
  * @brief   An implementation to write a 16bit rgb image buffer to a jpeg file.
	*
  ******************************************************************************
  */ 
	
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include <stdint.h>
#include <string.h>
#include "jpeglib.h"
#include "jpeg_write.h"
#include "jpeg_rgb.h"

/** @addtogroup JPEG_MODULE
  * @{
  */

/** @defgroup JPEG_WRITE
  * @{
  */
	
/** @defgroup JPEG_WRITE_Public
  * @{
  */
  
	
void jpeg_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height)
{ 
    
  struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	JSAMPROW row_pointer[1];		/* pointer to JSAMPLE row[s] */
	
	/* Step 1: allocate and initialize JPEG compression object */
	
	/* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);
	
	/* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  jpeg_stdio_dest(&cinfo, file);
	
	/* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = (unsigned int)img_width; 	/* image width and height, in pixels */
  cinfo.image_height = (unsigned int)img_height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
	 
	 /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
	
	/* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);
	
	/* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
	 
	// RGB masks for conversion
	uint16_t red_mask = 0xF800;
	uint16_t green_mask = 0x7E0;
	uint16_t blue_mask = 0x1F;
	
	uint16_t *pixel = (uint16_t *)buffer + img_width*img_height;
	
  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
		
		// Convert row of buffer from RGB565 to RGB888
		uint8_t *Pixels_RGB888 = (uint8_t *)malloc(img_width * 3);
		//uint8_t Pixels_RGB888[480 * 3] = {0};
		//uint16_t *pixel = (uint16_t *)(buffer + cinfo.next_scanline * img_width * 2);
		int i;
		for(i = 0; i < img_width; i++)
		{
			
			// Convert RGB16 to RGB888
			uint8_t R5 = (*pixel & red_mask) >> 11;
			uint8_t G6 = (*pixel & green_mask) >> 5;
			uint8_t B5 = (*pixel & blue_mask);		

			uint8_t R8 = ( R5 * 527 + 23 ) >> 6;
			uint8_t G8 = ( G6 * 259 + 33 ) >> 6;
			uint8_t B8 = ( B5 * 527 + 23 ) >> 6;
			
			// Put RGB values in new array
			Pixels_RGB888[i*3] 	 = R8;
			Pixels_RGB888[i*3+1] = G8;
			Pixels_RGB888[i*3+2] = B8;
			
			//increment pixel
			pixel++;
		}
		
		// To flip the image
		pixel -= img_width * 2;
		
    row_pointer[0] = Pixels_RGB888;
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
		
		// Delete pixels
		free(Pixels_RGB888);
  }
	
	/* Step 6: Finish compression */
  jpeg_finish_compress(&cinfo);
	
	
	/* Step 7: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);
	
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
