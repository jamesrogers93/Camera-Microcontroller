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
#include "sdcard_module.h"

#include "stm32746g_discovery.h"

// FatFs
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

char SD_Path[4];
FATFS fs;

uint8_t SDCard_Initalise(void)
{
	if(BSP_SD_Init() != MSD_OK)
	{
		return SDCARD_ERROR_INITALISE;
	}
	
	// Link the SD Card disk I/O driver
  if(FATFS_LinkDriver(&SD_Driver, SD_Path) != 0)
  {
		return SDCARD_ERROR_DRIVER;
	}
	
	return SDCARD_OK;
}

uint8_t SDCard_IsDetected(void)
{
	return BSP_SD_IsDetected() == SD_PRESENT;
}

uint8_t SDCard_OpenFile(FIL *file, const char *filePath, uint8_t mode)
{
	  // Open filesystem
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return SDCARD_ERROR_FILE;
  }
	
	// Open file
	FRESULT res = f_open(file, (TCHAR const*)filePath, mode);
	if( res != FR_OK)
  {
		return SDCARD_ERROR_FILE;
	}
	
	return SDCARD_OK;
}

uint8_t SDCard_CloseFile(FIL *file)
{
	f_close (file);
	f_mount(NULL, (TCHAR const*)"",0);
	
	return SDCARD_OK;
}

uint8_t SDCard_GetBMPFileName(uint16_t *numFiles, const char* DirName, char* Files[], const unsigned int maxFiles, const unsigned int maxFileName, const unsigned int startIndex)
{
  FILINFO fno;
  DIR dir;
  uint16_t counter = 0, index = 0;
  FRESULT res;
	
	uint8_t bmpCount = 0;

  /* Open filesystem */
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return SDCARD_ERROR_FILE;
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
	
	*(numFiles) = index;
	
  return SDCARD_OK;
}

uint8_t SDCard_GetNumFileType(uint16_t *numFiles, const char* DirName, const char* FileType, const uint8_t FileTypeLen)
{
  FILINFO fno;
  DIR dir;
  uint32_t counter = 0;//, index = 0;
  FRESULT res;
	
	uint16_t fileCount = 0;

  /* Open filesystem */
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return SDCARD_ERROR_FILE;
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
				// Iterate over file name untill we reach . i.e. the extension
        do
        {
          counter++;
        }
        while (fno.fname[counter] != 0x2E); /* . */

				// Check if the file extension matches
				int i;
				for(i = 0; i < FileTypeLen; i++)
				{
					if(fno.fname[counter + 1 + i] != FileType[i])
					{
						break;
					}
				}
				
				// We have found a file, increment the counter
				fileCount++;
      }
    }
  }
	
  f_mount(NULL, (TCHAR const*)"",0);
	
	*(numFiles) = fileCount;
	
  return SDCARD_OK;
}