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
#include "stm32746g_discovery_sd.h"

void SDCard_Config(void)
{
	BSP_SD_Init();
}

int SDCard_IsDetected(void)
{
	return BSP_SD_IsDetected() == SD_PRESENT;
}
