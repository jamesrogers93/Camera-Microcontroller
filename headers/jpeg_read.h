#ifndef __JPEG_READ_H
#define __JPEG_READ_H

#include "ff.h"

#define JPGREAD_OK		((uint8_t)0x00)
#define JPGREAD_ERROR	((uint8_t)0x01)

void jpeg_read(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height);

#endif /* __JPEG_READ_H */
