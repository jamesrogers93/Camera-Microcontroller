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

FATFS SD_FatFs;  /* File system object for SD card logical drive */
char SD_Path[4];

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
