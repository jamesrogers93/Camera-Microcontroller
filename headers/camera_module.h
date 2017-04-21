
#ifndef _CAMERA_MODULE_H
#define _CAMERA_MODULE_H

#include "stdint.h"

#define CAMERAMOD_OK		 ((uint8_t)0x00)
#define CAMERAMOD_ERROR  ((uint8_t)0x01)

uint8_t Camera_Initalise(void);

void Camera_Continuous(uint8_t *buffer);
void Camera_Snapshot(uint16_t *buffer);
void Camera_Resume(void);
void Camera_Pause(void);

#endif /* _CAMERA_MODULE_H */
