#ifndef _CAMERA_GLOBALS_H
#define _CAMERA_GLOBALS_H

#include <stdint.h>

#define CAMERA_GLOBAL_DRAWON 1
#define CAMERA_GLOBAL_DRAWOFF 0

#define CAMERA_GLOBAL_BUFFER 0xC0260000


// DELETE
#define IMAGE_HEIGHT 48
#define IMAGE_WIDTH  48
//DELETE

uint32_t Camera_BufferAddress(void);

#endif /* _CAMERA_GLOBALS_H */
