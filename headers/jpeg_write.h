#ifndef __JPEG_WRITE_H
#define __JPEG_WRITE_H

#include "ff.h"

#define JPGWRITE_OK			((uint8_t)0x00)
#define JPGWRITE_ERROR	((uint8_t)0x01)

void jpeg_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height);

#endif /* __JPEG_DECODE_H */
