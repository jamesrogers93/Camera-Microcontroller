#include "Bmp_Write.h"
#include "Bmp_FileHeader.h"

int bmp_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height, uint16_t target_width, uint16_t target_height)
{
	
	/*uint16_t *Camera_ptr = (uint16_t *)buffer;
	int t;
	for(t = 0; t < 272; t++)
	{
		int j;
		for(j = 0; j < 480; j++)
		{
			*Camera_ptr++ = 0xF800;
		}	
	}*/
	
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
	//bitMapHeader.pixel_data = 
	
	
	// image is 480 x 272.
	// we want to resize it to 48x48 without warping it.
	// sample from the center of the image or dims 272x272.
	// for easy conversion to 48x48, we are instead going to sample from 240x240 as 48*5 < 272 && 48*6 > 272.
	uint16_t resampleSize = 240;
	uint16_t width = 480;
	uint16_t height = 272;
	
	uint16_t discardRows = ((height - resampleSize) * 0.5);
	uint16_t discardColums = ((width - resampleSize) * 0.5);
	
	// A pixel pointer to the start position in the image buffer
	uint16_t *pixel = (uint16_t *)buffer + (discardRows * width + discardColums);
	
	// A predefined array of neighbouring pixel indexes
	int16_t pixelIndex[9] = {-2, -1, 1, 2, 0, -width*2, -width, width, width*2}; //{leftleft, left, right, rightright, center, belowbelow, below, aboveabove}
	
	// The new pixels array with the resized image.
	uint16_t pixels[48 * 48] = {0};
	uint32_t counter = 0;
	
	// RGB masks for conversion
	uint16_t red_mask = 0xF800;
	uint16_t green_mask = 0x7E0;
	uint16_t blue_mask = 0x1F;
	
	int i;
	for(i = 0; i < 48; i++)
	{
		
		int j;
		for(j = 0; j < 48; j++)
		{
			// Use 9 nearest neighbours to calculate colour

			// Calculate 9 nearest neighbour average
			
			// The RGB values that will be accumulated
			uint16_t R = 0, G = 0, B = 0;
			
			// The pixel from the image buffer
			uint16_t pix = 0;
			
			int k;
			for(k = 0; k < 9; k++)
			{
				// Get a neighnouring pixel from the image buffer
				pix = *(pixel + pixelIndex[k]);
				
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
			
			// Divide by nine for average.
			//float i9 = 1/9;
			R /= 9;
			G /= 9;
			B /= 9;
			
			// Convert RGB88 back to RGB16
			uint8_t R5 = R  >> 3;  // 5-bit red
			uint8_t G6 = G  >> 2;  // 6-bit green
			uint8_t B5 = B  >> 3;  // 5-bit blue
			uint16_t colour16 = (uint16_t) B5 + (G6<<5) + (R5<<(5+6));
			
			// Place new pixel in new image
			pixels[counter] = colour16;
			
			// Increment pixel index
			counter++;
			
			// Increment pixel pointer
			pixel += 5;
		}
		
		// Move pixel pointer to next row
		pixel += discardColums * 2; // times 2 for colums on both sides
		
	}
	
	// Write the header to file
	uint32_t BytesRead = 0;
	if(f_write(file, &bitMapHeader, sizeof(bitMapHeader), &BytesRead) != FR_OK)
	{
		while(1){}
	}
	
	// Move file pointer to bmp pixel data
	if(f_lseek(file, bitMapHeader.DataOffSet) != FR_OK)
	{
		while(1){}
	}
	
	// Write bitmap to bmp file
	if(f_write(file, &pixels, bitMapHeader.Width * bitMapHeader.Height * 2, &BytesRead) != FR_OK)
	{
		while(1){}
	}
}