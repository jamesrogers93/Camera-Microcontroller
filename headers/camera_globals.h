#ifndef _CAMERA_GLOBALS_H
#define _CAMERA_GLOBALS_H

#include <stdint.h>

// GLCD defines
#define GLCD_CAMERA_WIDTH GLCD_WIDTH
#define GLCD_CAMERA_HEIGHT	GLCD_HEIGHT
#define GLCD_CAMERA_WIDTH_HALF GLCD_WIDTH * 0.5
#define GLCD_CAMERA_HEIGHT_HALF	GLCD_HEIGHT * 0.5
#define GLCD_CAMERA_EDGE_PADDING 5
#define GLCD_CHAR_WIDTH 16

// Message defines
#define CAMERA_SDCARD_PROMPT_MSG "INSERT SDCARD"
#define CAMERA_SDCARD_PROMPT_MSG_LEN 13

#define CAMERA_GLOBAL_DRAWON 1
#define CAMERA_GLOBAL_DRAWOFF 0

#define PHOTO_DIRECTORY "Media/Photos"
#define PHOTO_ICONDIRECTORY "Media/Icons"

enum CAMERA_STATE {CAMERA_VIEW, CAMERA_PHOTOS};
enum CAMERA_PHOTOS_STATE {CAMERA_PHOTOS_PREVIEWS, CAMERA_PHOTOS_PHOTO};


uint32_t Camera_BufferAddress(void);

#endif /* _CAMERA_GLOBALS_H */