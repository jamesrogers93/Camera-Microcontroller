#ifndef _BMP_READ_H
#define _BMP_READ_H

#include <stdint.h>
#include "ff.h"

#define BMPREAD_OK		((uint8_t)0x00)
#define BMPREAD_ERROR	((uint8_t)0x01)

uint8_t bmp_read(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height);

#endif /* _BMP_READ_H */
