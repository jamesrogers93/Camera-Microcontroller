
#ifndef _CAMERA_SHARED_H
#define _CAMERA_SHARED_H

#include <stdint.h>

#define CAMERA_OK				((uint8_t)0x00)
#define CAMERA_ERROR		((uint8_t)0x01)

#define CAMERA_DRAWON 	((uint8_t)0x00)
#define CAMERA_DRAWOFF 	((uint8_t)0x01)

extern uint8_t(*camera_state_ptr)(void);

extern uint8_t Camera_DrawToScreen;

uint32_t ImageBufferAddress(void);

#endif /* _CAMERA_SHARED_H */
