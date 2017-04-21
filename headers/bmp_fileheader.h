#ifndef _BMP_FILEHEADER_H
#define _BMP_FILEHEADER_H

#pragma pack(push, 1)
typedef struct BitMap
{
    short Signature;
    long Reserved1;
    long Reserved2;
    long DataOffSet;

    long Size;
    long Width;
    long Height;
    short Planes;
    short BitsPerPixel;
    long Compression;
    long SizeImage;
    long XPixelsPreMeter;
    long YPixelsPreMeter;
    long ColorsUsed;
    long ColorsImportant;
    unsigned char *pixel_data;
}BitMap;
#pragma pack(pop)

#endif /* _BMP_FILEHEADER_H */
