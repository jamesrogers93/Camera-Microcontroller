#ifndef _CAMERA_STATES_H
#define _CAMERA_STATES_H

#include <stdint.h>

uint8_t camera_cameraview_run(void);
uint8_t camera_photopreviews_run(void);
uint8_t camera_photospecific_run(void);
uint8_t camera_sdprompt_run(void);
uint8_t camera_takepicture_run(void);

#endif /* _CAMERA_STATES_H */
