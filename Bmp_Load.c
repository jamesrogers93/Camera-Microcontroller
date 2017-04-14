
#include "Bmp_Load.h"
#include "Bmp_FileHeader.h"

uint8_t sector[512];
uint32_t BytesRead = 0;

int bmp_process(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height)
{
	uint8_t status;
	BitMap bitMapHeader;
	
	// Read bmp header
  if (f_read (file, &bitMapHeader, sizeof(BitMap), (UINT *)&BytesRead) == FR_OK)
	{
		// Check if file loaded is a bitmap
		if(bitMapHeader.Signature != 0x4D42)
		{
			return 0;
		}
	}
	
	// Store image dimensions
	*(img_width) = (uint16_t)bitMapHeader.Width;
	*(img_height) = (uint16_t)bitMapHeader.Height;
	
	status = 0;
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
			
		status = 1;

	}
	
	return status;
}