#include "Camera_View.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Camera
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_camera.h"

// Touch
#include "Touch_Handler.h"

// Camera application
#include "Camera_Defines.h"
#include "Camera_Globals.h"
#include "Icons/Icon_Photos.c"

DMA2D_HandleTypeDef hdma2d_eval;

extern unsigned char *buffer;

extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

Entity Camera_ViewEntities[1];
unsigned int num_viewEntities;


static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst);

void Camera_View_Initalise(void)
{
	
	BSP_CAMERA_Init(resolution);
	
	Camera_ViewEntities[0] = Entity_Make(
																				Point_2D_Make(
																											GLCD_CAMERA_WIDTH-Icon_Photos.width - GLCD_CAMERA_EDGE_PADDING, 
																											GLCD_CAMERA_HEIGHT-Icon_Photos.height - GLCD_CAMERA_EDGE_PADDING), 
																				&Icon_Photos);
	num_viewEntities = 1;
}

enum CAMERA_STATE Camera_View_Run(void)
{
	
	BSP_CAMERA_ContinuousStart((uint8_t *)buffer);

	//BSP_CAMERA_LineEventCallback();
	// Check if we can draw to screen.
	// This prevents us from drawing the same thing to the screen every cycle.
	if(Camera_Global_DrawToScreen == CAMERA_GLOBAL_DRAWON)
	{
		// Lock the draw to screen flag.
		Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWOFF;
		
		// Draw the state string to the screen.
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Camera State");
		
		// Draw the photos icon to the screen.
		GLCD_DrawBitmap( 
										Camera_ViewEntities[0].position.x, 
										Camera_ViewEntities[0].position.y, 
										Camera_ViewEntities[0].image->width,
										Camera_ViewEntities[0].image->height, 
										Camera_ViewEntities[0].image->pixel_data);
	}
	
	// Check if the photos icon has been pressed.
	Point_2D point;
	if(Screen_Touched(&point))
	{
		// Check if the touch position collides with the entities.
		if(Point_Entity_Collision(&point, Camera_ViewEntities, num_viewEntities) != 0)
		{
			GLCD_ClearScreen();
			
			// Release the draw to screen flag, enabling items to be drawn again.
			Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
			
			// Return the next state.
			return CAMERA_PHOTOS;
		}
	}
	
	// Remain in the same state/
	return CAMERA_VIEW;
}

void BSP_CAMERA_LineEventCallback(void)
{
  static uint32_t tmp, tmp2, counter;

  if(ysize > counter)
  {
    LCD_LL_ConvertLineToARGB8888((uint32_t *)(buffer + tmp), (uint32_t *)(GLCD_FrameBufferAddress() + tmp2));
    tmp  = tmp + xsize*sizeof(uint16_t);
    tmp2 = tmp2 + xsize*sizeof(uint32_t);
    counter++;
  }
  else
  {
    tmp = 0;
    tmp2 = 0;
    counter = 0;
  }
}

static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst)
{
  /* Enable DMA2D clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888;
  hdma2d_eval.Init.OutputOffset = 0;

  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d_eval.LayerCfg[1].InputColorMode = CM_RGB565;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;

  hdma2d_eval.Instance = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, xsize, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
  }
  else
  {
    /* FatFs Initialization Error */
    while(1);
  }
}
