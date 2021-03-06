//
// Created by egor on 27.11.17.
//
#pragma once
#include <stdint.h>

#pragma pack(push, 2)
typedef struct{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;

    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmpHeader_s;
#pragma pack(pop)

typedef struct {
    unsigned char red, green, blue;
} pixel_s;

typedef struct {
    uint32_t width, height;
    pixel_s* data;
} image_s;

