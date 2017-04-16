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
#include "Jpeg_Decode.h"

extern GLCD_FONT     GLCD_Font_16x24;

char SD_Path[4];
//uint8_t sector[512];
FATFS fs;
//uint32_t BytesRead = 0;

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

int SDCard_OpenFile(FIL *file, const char *filePath, uint8_t mode)
{
	  // Open filesystem
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }
	
	// Open file
	FRESULT res = f_open(file, (TCHAR const*)filePath, mode);
	if( res != FR_OK)
  {
		return 0;
	}
	
	return 1;
}

int SDCard_CloseFile(FIL *file)
{
	f_close (file);
	f_mount(NULL, (TCHAR const*)"",0);
	
	return 1;
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
