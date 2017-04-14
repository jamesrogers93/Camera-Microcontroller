

#include "Jpeg_Decode.h"
#include "Camera_Globals.h"
#include "Jpeg_RGB.h"

//extern unsigned char *buffer;
uint32_t  offset = 0;
RGB_typedef *RGB_matrix;

 struct jpeg_decompress_struct cinfo;
 struct jpeg_error_mgr jerr;
  
	
void jpeg_decode(JFILE *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height)
{ 
    
  /* Decode JPEG Image */
  JSAMPROW jBuffer[2] = {0}; /* Output row buffer */
  uint32_t row_stride = 0; /* physical row width in image buffer */
  
  /* Step 1: allocate and initialize JPEG decompression object */
  cinfo.err = jpeg_std_error(&jerr);
	
  /* Initialize the JPEG decompression object */  
  jpeg_create_decompress(&cinfo);
  
  jpeg_stdio_src (&cinfo, file);

  /* Step 3: read image parameters with jpeg_read_header() */
  jpeg_read_header(&cinfo, TRUE);

  /* TBC */
  /* Step 4: set parameters for decompression */
  cinfo.dct_method = JDCT_FLOAT;

  /* Step 5: start decompressor */
  jpeg_start_decompress(&cinfo);
	
	row_stride = cinfo.output_width * cinfo.output_components;
	jBuffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * row_stride);

	uint32_t line_counter = 0;
  while (cinfo.output_scanline < cinfo.output_height)
  {
    (void) jpeg_read_scanlines(&cinfo, jBuffer, 1);
    
    /* TBC */
    if (processBuffer(jBuffer[0], buffer, line_counter, cinfo.output_width, cinfo.output_height) == 0)
    {
      break;
    }
		
		line_counter++;
  }

	// Save the image dimensions
	*(img_width) = cinfo.output_width;
	*(img_height) = cinfo.output_height;
	
  /* Step 6: Finish decompression */
  jpeg_finish_decompress(&cinfo);

  /* Step 7: Release JPEG decompression object */
  jpeg_destroy_decompress(&cinfo);
    
}

static uint8_t processBuffer(uint8_t* Row, uint8_t *buffer, uint32_t rowNum, uint16_t width, uint16_t height)
{
	offset = ((uint32_t)buffer + (width * (height - rowNum) * 2));
	RGB_matrix =  (RGB_typedef*)Row;
	int index = 0;
	for (index = 0; index < width; index++)
  {
		// Convert RGB888 to RGB565.
		// Also swap RB.
		uint8_t Red16   = RGB_matrix[index].B  >> 3;  // 5-bit red
    uint8_t Green16 = RGB_matrix[index].G  >> 2;  // 6-bit green
    uint8_t Blue16  = RGB_matrix[index].R  >> 3;  // 5-bit blue
		
		unsigned short col = (unsigned short) Blue16 + (Green16<<5) + (Red16<<(5+6));

		*(__IO uint8_t*) (offset) = *((uint8_t *)&col);
		offset++;
		*(__IO uint8_t*) (offset) = *((uint8_t *)&col+1); 
		offset++;
	}  
	
	return 1;
}