
#include "camera_shared.h"

#include "GLCD_Config.h"

uint8_t Camera_DrawToScreen = CAMERA_DRAWON;

uint32_t photoSpecificID = 0;

static uint16_t image_buffer[GLCD_WIDTH*GLCD_HEIGHT] __attribute__((at(0xC0260000)));

uint32_t ImageBufferAddress(void)
{
	return ((uint32_t)image_buffer);
}
