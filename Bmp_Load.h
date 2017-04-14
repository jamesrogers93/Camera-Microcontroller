#ifndef _BMP_LOAD_H
#define _BMP_LOAD_H

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

int bmp_process(FIL *file, uint8_t *buffer, uint16_t *img_width, uint16_t *img_height);

#endif /* _BMP_LOAD_H */