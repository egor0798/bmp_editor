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
