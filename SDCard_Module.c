/**
  ******************************************************************************
  * @file    SDCard.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   This file provides functions for the SDCard
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "SDCard_Module.h"

#include "Camera_Defines.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

extern GLCD_FONT     GLCD_Font_16x24;

char SD_Path[4];
uint8_t sector[512];
FATFS fs;
uint32_t BytesRead = 0;

void SDCard_Config(void)
{
	BSP_SD_Init();
	
	// Link the SD Card disk I/O driver
  if(FATFS_LinkDriver(&SD_Driver, SD_Path) != 0)
  {
		// Draw the state string to the screen
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "SDCard Driver Error");
	
		while(1){}
	}
}

int SDCard_IsDetected(void)
{
	return BSP_SD_IsDetected() == SD_PRESENT;
}

int SDCard_loadBMP(unsigned char *buffer, const char* filePath)
{
  FIL F1;
	BitMap bitMapHeader;
	int status = 0;
	
	// Open filesystem 
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }
	
	// Open file
  if (f_open(&F1, (TCHAR const*)filePath, FA_READ) == FR_OK)
  {
		// Read bmp header
    if (f_read (&F1, &bitMapHeader, sizeof(BitMap), (UINT *)&BytesRead) == FR_OK)
		{
			// Check if file loaded is a bitmap
			if(bitMapHeader.Signature == 0x4D42)
			{
				status = 1;
			}
		}
  }
	
	// If file was loaded
	if(status)
	{
		status = 0;
		
		// Move file pointer to bmp pixel data
		if(f_lseek(&F1, bitMapHeader.DataOffSet) == FR_OK)
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
				f_read (&F1, sector, i1, (UINT *)&BytesRead);
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
	}
	
	f_close (&F1);
	f_mount(NULL, (TCHAR const*)"",0);
	return status;
}

int SDCard_GetBMPFileName(const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex)
{
  FILINFO fno;
  DIR dir;
  uint32_t counter = 0, index = 0;
  FRESULT res;
	
	unsigned int bmpCount = 0;

  /* Open filesystem */
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }

  /* Open directory */
  res = f_opendir(&dir, (TCHAR const*)DirName);
  
  if (res == FR_OK)
  {
    for (;;)
    {
			// Read the file
      res = f_readdir(&dir, &fno);
      if (res != FR_OK || fno.fname[0] == 0)
        break;
			
			// Check if the begining of the file name = . or _
			// IF true, skip this file
      if (fno.fname[0] == '.' || fno.fname[0] == '_')
        continue;

      if (!(fno.fattrib & AM_DIR))
      {
				// Iterate over filen name untill we reach . i.e. the extension
        do
        {
          counter++;
        }
        while (fno.fname[counter] != 0x2E); /* . */

				// Check if the max number of files has been reached
        if (index < maxFiles)
        {
					// Check that the extension = bmp
          if ((fno.fname[counter + 1] == 'B') && (fno.fname[counter + 2] == 'M') && (fno.fname[counter + 3] == 'P'))
          {
						// Check we are at the start index.
						// I.E. If startIndex = 8, we want to load the directories from the 8th bmp
						if(bmpCount >= startIndex)
						{
							// Check if the file name does not exceed the filename character limit
							if(sizeof(fno.fname) <= (maxFileName + 2))
							{
								sprintf (Files[index], "%s", fno.fname);
								index++;
							}
						}
						
						// We have found a bmp file, increment the bmp counter
						bmpCount++;
          }
        }
        counter = 0;
      }
    }
  }
	
  f_mount(NULL, (TCHAR const*)"",0);
  return index;
}

#include "Camera_Globals.h"
extern unsigned char *buffer;
uint8_t   _aucLine[256];
uint32_t  offset = 0;
RGB_typedef *RGB_matrix;
static uint8_t processBuffer(uint8_t* Row, uint32_t rowNum, uint16_t width, uint16_t height);

int SDCard_loadJPEG(unsigned char *buff, const char* filePath, uint16_t *imgWidth,uint16_t *imgHeight)
{
	FIL file;

  // Open filesystem
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }
	
	// Open file
	FRESULT res = f_open(&file, (TCHAR const*)filePath, FA_READ);
	if( res != FR_OK)
  {
		return 0;
	}

	//
	jpeg_decode(&file, imgWidth, imgHeight, _aucLine, processBuffer);
	
	f_close (&file);
	f_mount(NULL, (TCHAR const*)"",0);
	
	return 1;
}

static uint8_t processBuffer(uint8_t* Row, uint32_t rowNum, uint16_t width, uint16_t height)
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
