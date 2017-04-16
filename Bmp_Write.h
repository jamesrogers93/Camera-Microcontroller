#ifndef _BMP_WRITE_H
#define _BMP_WRITE_H

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

int bmp_write(FIL *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height, uint16_t target_width, uint16_t target_height);

#endif /* _BMP_LOAD_H */