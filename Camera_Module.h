
#ifndef _CAMERA_MODULE_H
#define _CAMERA_MODULE_H

// BSP Camera
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_camera.h"

#define resolution      RESOLUTION_R480x272
#define xsize           480
#define ysize           272
//#define CAMERA_FRAME_BUFFER               0xC0260000


void Camera_Config(void);

void Camera_Continuous(uint8_t *buffer);
void Camera_Snapshot(uint8_t *buffer);
void Camera_Resume(void);
void Camera_Pause(void);

#endif /* _CAMERA_MODULE_H */
