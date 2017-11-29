//
// Created by egor on 27.11.17.
//

#include <malloc.h>
#include "../include/inOut.h"

read_code read_header(FILE* in, bmpHeader_s* header ){
    read_code res;
    res = 1 == 1 ? READ_OK : READ_INVALID_HEADER;
    fread(header, sizeof(bmpHeader_s), 1, in);
    return res;
}

read_code read_data(FILE* in, image_s* src){
    bmpHeader_s header;
    read_code res = read_header(in, &header);
    short offset;
    if(in == NULL)
        return MISSING_FILE;
    if(header.bfType != 0x4d42)
        return READ_INVALID_FORMAT;
    offset = header.biWidth*sizeof(pixel_s)%4;
    if(offset != 0)
        offset = 4 - offset;
    src->height = header.biHeight;
    src->width = header.biWidth;
    src->data = (pixel_s*)malloc(sizeof(pixel_s)*src->height*src->width);
    fseek(in, header.bOffBits, SEEK_SET);
    for (int i = 0; i < src->height; ++i) {
        for (int j = 0; j < src->width; ++j)
            fread(&src->data[i*src->width + j], sizeof(pixel_s), 1, in);
        fseek(in, offset, SEEK_CUR);
    }
    return READ_OK;
}


write_code to_bmp(FILE* output, image_s* image)
{
    int i, j;
    bmpHeader_s  header;
    int offset;
    offset = image->width * sizeof(pixel_s) % 4;
    if(offset != 0)
    {
        offset = 4 - offset;
    }
    header.bfType = 0x4d42;
    header.bfileSize = 54 + (image->width*3 + offset) * image->height;
    header.bfReserved = 0;
    header.bOffBits = 54;
    header.biSize = 40;

    header.biWidth = image->width;
    header.biHeight = image->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = image->width*image->height*3;
    header.biXPelsPerMeter = 0xb13;
    header.biYPelsPerMeter = 0xb13;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    fwrite(&header, sizeof(bmpHeader_s), 1, output);
    fseek(output, 54, SEEK_SET);
    for(i = 0; i < image->height; i++)
    {
        for(j = 0; j < image->width; j++)
        {
            fwrite(&image->data[i*(image->width) + j], sizeof(pixel_s), 1, output);
        }
        fseek(output, offset, SEEK_CUR);
    }
    return WRITE_OK;
}
