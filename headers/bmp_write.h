#ifndef _BMP_WRITE_H
#define _BMP_WRITE_H

#include <stdint.h>
#include "ff.h"

#define BMPWRITE_OK			((uint8_t)0x00)
#define BMPWRITE_ERROR	((uint8_t)0x01)

uint8_t bmp_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height, uint16_t target_width, uint16_t target_height);

#endif /* _BMP_WRITE_H */
