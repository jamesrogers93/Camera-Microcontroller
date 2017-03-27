
#ifndef _CAMERA_H
#define _CAMERA_H

enum CAMERA_STATE {CAMERA_VIEW, CAMERA_BROWSE};

void Camera_initalise(void);

void Camera_run(void);

void Camera_PromptSDCard(void);

#endif /* _CAMERA_H */
