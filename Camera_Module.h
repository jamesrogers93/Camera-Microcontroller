
#ifndef _CAMERA_MODULE_H
#define _CAMERA_MODULE_H

#define resolution      RESOLUTION_R480x272
#define xsize           480
#define ysize           272
//#define CAMERA_FRAME_BUFFER               0xC0260000


void Camera_Config(void);

void Camera_Start(void);
void Camera_Stop(void);

#endif /* _CAMERA_MODULE_H */
