/**
  ******************************************************************************
  * @file    SDCard.h 
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    25-March-2017
  * @brief   This file provides functions for the SDCard
  ******************************************************************************
  */
	
#ifndef _SDCARD_MODULE_H
#define _SDCARD_MODULE_H

#include "stm32746g_discovery.h"
#include <stdlib.h>
#include "fatfs_storage.h"

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

void SDCard_Config(void);

int SDCard_IsDetected(void);
	

#endif /* _SDCARD_MODULE_H */

