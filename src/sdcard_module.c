/**
  ******************************************************************************
  * @file    sdcard_module.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   An implementation for communicating with an SD card.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sdcard_module.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sd.h"     // Keil.STM32F746G-Discovery::Board Support:Drivers:SD
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/** @addtogroup SDCARD_MODULE
  * @{
  */
	
/** @defgroup SDCARD_MODULE_Private_Variables
  * @{
  */

/**
  * @brief The path to the SD card
  */
char SD_Path[4];

/**
  * @brief The FatFS file system
  */
FATFS fs;

/**
  * @}
  */
	
/** @addtogroup SDCARD_MODULE_Public_Functions
  * @{
  */

/**
  * @brief  Initializes the SD card.
  * @retval Status: SD card status
  */
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

/**
  * @brief  Checks if the SD card is detected.
  * @retval Status: SD card status
  */
uint8_t SDCard_IsDetected(void)
{
	if(BSP_SD_IsDetected() == SD_PRESENT)
	{
		return SDCARD_OK;
	}
	else
	{	
		return SDCARD_ERROR_DETECTED;
	}
}

/**
  * @brief  Opens a file from the SD card.
	* @param	Fil: A pointer to a file object
	* @param	filePath: The file path to the file
	* @param	mode: The file open mode
  * @retval Status: SD card status
  */
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

/**
  * @brief  Closes a file in the SD card.
	* @param	Fil: A pointer to a file object
  * @retval Status: SD card status
  */
uint8_t SDCard_CloseFile(FIL *file)
{
	f_close (file);
	f_mount(NULL, (TCHAR const*)"",0);
	
	return SDCARD_OK;
}

/**
  * @brief  Gets BMP file names from the SD card.
	* @param	numFiles: Will equal to the number of bmp files found
	* @param	DirName: The directory path
	* @param	Files: An array which will be filled of bmp file names found
	* @param	maxFiles: The max number of files to be read
	* @param	maxFileName: The max size of the file names
	* @param 	startIndex: The files index to start navigating
  * @retval Status: SD card status
  */
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

/**
  * @brief  Gets BMP file names from the SD card.
	* @param	numFiles: Will equal to the number of bmp files found
	* @param	DirName: The directory path
	* @param	FileType: The file type to be found
	* @param	FileTypeLen: The max length of the files retrieved
  * @retval Status: SD card status
  */
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

/**
  * @}
  */ 

/**
  * @}
  */ 
