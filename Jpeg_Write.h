#ifndef __JPEG_WRITE_H
#define __JPEG_WRITE_H

/* FatFs includes component */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

/* Jpeg includes component */
#include <stdint.h>
#include <string.h>
#include "jpeglib.h"

void jpeg_write(JFILE *file, uint8_t *buffer, uint16_t img_width, uint16_t img_height);

//static uint8_t processBuffer(uint8_t* Row, uint8_t *buffer, uint32_t rowNum, uint16_t width, uint16_t height);

#endif /* __JPEG_DECODE_H */