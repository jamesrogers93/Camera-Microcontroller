/**
  ******************************************************************************
  * @file    camera_module.c
  * @author  j.rogers2@uea.ac.uk
  * @version V1.0.0
  * @date    03-05-2017
  * @brief   An interface for communicating with a camera connected through DCMI.
	*
  ******************************************************************************
  */ 
	
/* Includes ------------------------------------------------------------------*/
#include "camera_module.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_camera.h"
#include "Board_GLCD.h"

/** @defgroup CAMERA_MODULE_Private_Defines
  * @{
  */

/**
  * @brief The resolution of the camera
  */
#define CAMERA_RESOLUTION      	RESOLUTION_R480x272

/**
  * @brief The width of the camera resolution
  */
#define CAMERA_WIDTH           	480

/**
  * @brief The width of the camera resolution
  */
#define CAMERA_HEIGHT          	272

/**
  * @brief The number of bytes per pixel
  */
#define CAMREA_BYTESPERPIXEL		2

/**
  * @}
  */ 

extern DCMI_HandleTypeDef  hDcmiHandler;

/** @addtogroup CAMERA_MODULE_Functions
  * @{
  */
	
/**
  * @brief  Initializes the camera.
  * @retval Status: Camera status
  */
uint8_t Camera_Initalise(void)
{
	if(BSP_CAMERA_Init(CAMERA_RESOLUTION) != CAMERA_OK)
	{
		return CAMERAMOD_ERROR;
	}
	return CAMERAMOD_OK;
}

/**
  * @brief  Resumes the camera stream.
  * @retval None
  */
void Camera_Resume(void)
{
	BSP_CAMERA_Resume();
}

/**
  * @brief  Pauses the camera stream.
  * @retval None
  */
void Camera_Pause(void)
{
	BSP_CAMERA_Suspend();
}

/**
  * @brief  Starts the camera in continuous mode.
	* @param  buffer: pointer to the camera output buffer
  * @retval None
  */
void Camera_Continuous(uint8_t *buffer)
{
	BSP_CAMERA_ContinuousStart(buffer);
}

/**
  * @brief  Captures a snapshot of the camera.
	* @param  buffer: pointer to the camera output buffer
  * @retval None
  */
void Camera_Snapshot(uint16_t *buffer)
{
	Camera_Pause();
	
	uint16_t *Camera_ptr = buffer;
	uint16_t *GLCD_ptr = (uint16_t *)GLCD_FrameBufferAddress() + CAMERA_WIDTH*(CAMERA_HEIGHT-1);
	int i;
	for(i = 0; i < CAMERA_HEIGHT; i++)
	{
		int j;
		for(j = 0; j < CAMERA_WIDTH; j++)
		{
			*Camera_ptr++ = *GLCD_ptr++;
		}	
		
		// To flip the image
		GLCD_ptr -= CAMERA_WIDTH * CAMREA_BYTESPERPIXEL;
	}
	
	Camera_Resume();
}

/**
  * @brief  Handles DCMI interrupt request.
  * @retval None
  */
void BSP_CAMERA_IRQHandler(void) 
{
  HAL_DCMI_IRQHandler(&hDcmiHandler);
}

/**
  * @brief  Handles DMA interrupt request.
  * @retval None
  */
void BSP_CAMERA_DMA_IRQHandler(void) 
{
  HAL_DMA_IRQHandler(hDcmiHandler.DMA_Handle);
}

/**
  * @}
  */ 
