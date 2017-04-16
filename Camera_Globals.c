#include "Camera_Globals.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

int Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;

static uint16_t buffer[GLCD_WIDTH*GLCD_HEIGHT] __attribute__((at(0xC0260000)));

uint32_t Camera_BufferAddress(void)
{
//	return 0xC0260000;
	return ((uint32_t)buffer);
}
