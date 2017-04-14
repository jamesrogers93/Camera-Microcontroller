
#ifndef _CAMERA_VIEW_H
#define _CAMERA_VIEW_H

#define resolution      RESOLUTION_R480x272
#define xsize           480
#define ysize           272
//#define CAMERA_FRAME_BUFFER               0xC0260000

void Camera_View_Initalise(void);

enum CAMERA_STATE Camera_View_Run(void);

#endif /* _CAMERA_VIEW_H */
