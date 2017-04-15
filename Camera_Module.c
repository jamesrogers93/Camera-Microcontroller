#include "Camera_Module.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// BSP Camera
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_camera.h"

// Camera Application
#include "Camera_Globals.h"
#include "Error_Message.h"

extern DCMI_HandleTypeDef  hDcmiHandler;

void Camera_Config(void)
{
	if(BSP_CAMERA_Init(resolution) != CAMERA_OK)
	{
		Error_DisplayMessage("Error: Camera Module");
	}
	
	BSP_CAMERA_ContinuousStart((uint8_t *)GLCD_FrameBufferAddress());
	BSP_CAMERA_Suspend();
}

void Camera_Start(void)
{
	BSP_CAMERA_Resume();
	//BSP_CAMERA_ContinuousStart((uint8_t *)GLCD_FrameBufferAddress());
}

void Camera_Stop(void)
{
	BSP_CAMERA_Suspend();
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