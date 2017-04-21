#include "camera_module.h"

// BSP Camera
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_camera.h"

// GLCD
#include "Board_GLCD.h"

#define CAMERA_RESOLUTION      	RESOLUTION_R480x272
#define CAMERA_WIDTH           	480
#define CAMERA_HEIGHT          	272
#define CAMREA_BYTESPERPIXEL		2

extern DCMI_HandleTypeDef  hDcmiHandler;

uint8_t Camera_Initalise(void)
{
	if(BSP_CAMERA_Init(CAMERA_RESOLUTION) != CAMERA_OK)
	{
		return CAMERAMOD_ERROR;
	}
	return CAMERAMOD_OK;
}

void Camera_Resume(void)
{
	BSP_CAMERA_Resume();
}

void Camera_Pause(void)
{
	BSP_CAMERA_Suspend();
}

void Camera_Continuous(uint8_t *buffer)
{
	BSP_CAMERA_ContinuousStart(buffer);
}

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
