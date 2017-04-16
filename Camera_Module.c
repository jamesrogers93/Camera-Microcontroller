#include "Camera_Module.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

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
	
	Camera_Continuous((uint8_t *)GLCD_FrameBufferAddress());
	BSP_CAMERA_Suspend();
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

void Camera_Snapshot(uint8_t *buffer)
{
	Camera_Pause();
	
	uint16_t *Camera_ptr = (uint16_t *)Camera_BufferAddress();
	uint16_t *GLCD_ptr = (uint16_t *)GLCD_FrameBufferAddress() + 480*271;
	int i;
	for(i = 0; i < 272; i++)
	{
		int j;
		for(j = 0; j < 480; j++)
		{
			*Camera_ptr++ = *GLCD_ptr++;
		}	
		
		// To flip the image
		GLCD_ptr -= 480 * 2;
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